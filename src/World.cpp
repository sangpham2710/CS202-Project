#include "World.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <algorithm>
#include <cmath>
#include <limits>
#include <map>
#include <random>
#include <vector>

#include "Constants.hpp"
#include "SettingsSingleton.hpp"
#include "SoundNode.hpp"
#include "TexturesSingleton.hpp"
#include "Utility.hpp"

World::World(sf::RenderWindow& window, FontHolder& fonts, SoundPlayer& sounds)
    : mWindow(window),
      mWorldView(window.getDefaultView()),
      mFonts(fonts),
      mSounds(sounds),
      mSceneGraph(),
      mSceneLayers(),
      mWorldBounds(0.f, 0.f, mWorldView.getSize().x + 400,
                   mWorldView.getSize().y),
      mSpawnPosition(
          Constants::BLOCK_SIZE * 8 + Constants::BLOCK_SIZE / 2,
          Constants::LANE_HEIGHT * 11 + Constants::LANE_HEIGHT / 2.f),
      mViewPosition(mWorldView.getSize().x / 2.f, mWorldView.getSize().y / 2.f),
      mPlayerCharacter(nullptr),
      mLevelManager(),
      mCommandQueue() {
    buildScene();
    mWorldView.setCenter(mViewPosition);
}

void World::update(sf::Time dt) {
    destroyObstaclesOutsideView();
    while (!mCommandQueue.isEmpty()) {
        mSceneGraph.onCommand(mCommandQueue.pop(), dt);
    }
    handleCollisions();
    mSceneGraph.removeWrecks();
    mSceneGraph.update(dt, mCommandQueue);
    adaptPlayerPosition();
    if (SettingsSingleton::getInstance().getIsLevelSaving()) {
        mLevelManager.saveLevel();
        SettingsSingleton::getInstance().setIsLevelSaving(false);
    }
}

void World::draw() {
    mWindow.setView(mWorldView);
    mWindow.draw(mSceneGraph);
}

CommandQueue& World::getCommandQueue() {
    return mCommandQueue;
}

bool World::hasAlivePlayer() const {
    return !mPlayerCharacter->isMarkedForRemoval();
}

bool World::hasPlayerReachedEnd() const {
    return mPlayerCharacter->getPosition().y <= Constants::LANE_HEIGHT;
}

void World::adaptPlayerPosition() {
    sf::FloatRect viewBounds = getViewBounds();

    sf::Vector2f position = mPlayerCharacter->getPosition();
    int halfBlockSize = Constants::BLOCK_SIZE / 2;
    position.x = std::max(position.x, viewBounds.left + halfBlockSize);
    position.x = std::min(position.x,
                          viewBounds.left + viewBounds.width - halfBlockSize);
    position.y = std::max(position.y, viewBounds.top + halfBlockSize);
    position.y = std::min(position.y,
                          viewBounds.top + viewBounds.height - halfBlockSize);
    mPlayerCharacter->setPosition(position);
}

bool matchesCategories(SceneNode::Pair& colliders, Category::Type type1,
                       Category::Type type2) {
    unsigned int category1 = colliders.first->getCategory();
    unsigned int category2 = colliders.second->getCategory();

    // Make sure first pair entry has category type1 and second has type2
    if (type1 & category1 && type2 & category2) {
        return true;
    } else if (type1 & category2 && type2 & category1) {
        std::swap(colliders.first, colliders.second);
        return true;
    } else {
        return false;
    }
}

void World::handleCollisions() {
    std::set<SceneNode::Pair> collisionPairs;
    mSceneGraph.checkSceneCollision(mSceneGraph, collisionPairs);

    for (SceneNode::Pair pair : collisionPairs) {
        if (matchesCategories(pair, Category::PlayerCharacter,
                              Category::Obstacle)) {
            auto& character = static_cast<Character&>(*pair.first);
            auto& obstacle = static_cast<Obstacle&>(*pair.second);

            auto characterPosition = character.getWorldPosition();
            auto obstaclePosition =
                obstacle.getWorldPosition() +
                sf::Vector2f(obstacle.getBoundingRect().width,
                             obstacle.getBoundingRect().height) *
                    0.5f;
            auto explosionPosition =
                (obstaclePosition - characterPosition) * 0.5f;
            character.setExplosionPosition(explosionPosition);
            character.destroy();
            obstacle.setTextureWrecked();
            character.setTextureWrecked();
            Command command;
            command.category = Category::Obstacle;
            // stop all obstacles
            command.action =
                derivedAction<Obstacle>([](Obstacle& obstacle, sf::Time) {
                    obstacle.setVelocity(0.0f, 0.0f);
                });
            mCommandQueue.push(command);
        }
    }
}

void World::buildScene() {
    for (std::size_t i = 0; i < LayerCount; ++i) {
        SceneNode::Ptr layer(new SceneNode());
        mSceneLayers[i] = layer.get();
        mSceneGraph.attachChild(std::move(layer));
    }

    sf::Texture& texture = TexturesSingleton::getInstance().getTextures().get(
        Textures::Background);
    sf::IntRect textureRect(mWorldBounds);
    texture.setRepeated(true);

    std::unique_ptr<SpriteNode> backgroundSprite(
        new SpriteNode(texture, textureRect));
    backgroundSprite->setPosition(mWorldBounds.left, mWorldBounds.top);
    mSceneLayers[Background]->attachChild(std::move(backgroundSprite));

    mLevelManager.setLevelNode(mSceneLayers[LevelLayer]);

    if (SettingsSingleton::getInstance().getIsLevelLoaded()) {
        mLevelManager.loadLevel(
            SettingsSingleton::getInstance().getLoadingLevelFilename());
        SettingsSingleton::getInstance().setIsLevelLoaded(false);
    } else {
        mLevelManager.generateLevel(
            SettingsSingleton::getInstance().getCurrentLevelNumber());
    }

    std::unique_ptr<Character> character(new Character());
    character->setPosition(mSpawnPosition);
    mPlayerCharacter = character.get();
    mSceneLayers[CharacterLayer]->attachChild(std::move(character));

    std::unique_ptr<SoundNode> soundNode(new SoundNode(mSounds));
    mSceneGraph.attachChild(std::move(soundNode));
}

void World::destroyObstaclesOutsideView() {
    Command command;
    command.category = Category::Obstacle;
    command.action = derivedAction<Obstacle>([this](Entity& e, sf::Time) {
        if (!getBattlefieldBounds().intersects(e.getBoundingRect())) {
            e.destroy();
        }
    });
    mCommandQueue.push(command);
}

sf::FloatRect World::getViewBounds() const {
    return sf::FloatRect(mWorldView.getCenter() - mWorldView.getSize() / 2.f,
                         mWorldView.getSize());
}

sf::FloatRect World::getBattlefieldBounds() const {
    // Return view bounds + some area at top, where enemies spawn
    sf::FloatRect bounds = getViewBounds();
    bounds.left -= 200;
    bounds.width += 400;
    return bounds;
}
