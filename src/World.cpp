#include "World.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <algorithm>
#include <cmath>
#include <limits>

#include "Constants.hpp"
#include "TexturesSingleton.hpp"

World::World(sf::RenderWindow& window, FontHolder& fonts)
    : mWindow(window),
      mWorldView(window.getDefaultView()),
      mFonts(fonts),
      mSceneGraph(),
      mSceneLayers(),
      mWorldBounds(0.f, 0.f, mWorldView.getSize().x + 400,
                   mWorldView.getSize().y),
      mSpawnPosition(Constants::BLOCK_SIZE * 8 + Constants::BLOCK_SIZE / 2,
                     Constants::LANE_HEIGHT / 2.f),
      mViewPosition(mWorldView.getSize().x / 2.f, mWorldView.getSize().y / 2.f),
      mPlayerCharacter(nullptr) {
    loadTextures();
    buildScene();
    mWorldView.setCenter(mViewPosition);
}

void World::update(sf::Time dt) {
    destroyObstaclesOutsideView();
    while (!mCommandQueue.isEmpty()) {
        mSceneGraph.onCommand(mCommandQueue.pop(), dt);
    }
    mSceneGraph.removeWrecks();
    mSceneGraph.update(dt, mCommandQueue);
    adaptPlayerPosition();
}

void World::draw() {
    mWindow.setView(mWorldView);
    mWindow.draw(mSceneGraph);
}

CommandQueue& World::getCommandQueue() {
    return mCommandQueue;
}

void World::loadTextures() {
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


    std::unique_ptr<Lane> laneNode0(
        new Lane(Lane::Type::Grass, Lane::Left, 100));
    laneNode0->setPosition(0, 0 * Constants::BLOCK_SIZE);
    mSceneLayers[Land]->attachChild(std::move(laneNode0));

    std::unique_ptr<Lane> laneNode1(
        new Lane(Lane::Type::LilyPadAbove, Lane::Right, 100));
    laneNode1->setPosition(0, 1 * Constants::BLOCK_SIZE);
    mSceneLayers[Land]->attachChild(std::move(laneNode1));

    std::unique_ptr<Lane> laneNode2(
        new Lane(Lane::Type::LilyPadBelow, Lane::Left, 100));
    laneNode2->setPosition(0, 2 * Constants::BLOCK_SIZE);
    mSceneLayers[Land]->attachChild(std::move(laneNode2));

    std::unique_ptr<Lane> laneNode3(
        new Lane(Lane::Type::LilyPadSingle, Lane::Right, 100));
    laneNode3->setPosition(0, 3 * Constants::BLOCK_SIZE);
    mSceneLayers[Land]->attachChild(std::move(laneNode3));

    std::unique_ptr<Lane> laneNode4(
        new Lane(Lane::Type::PavementAbove, Lane::Left, 100));
    laneNode4->setPosition(0, 4 * Constants::BLOCK_SIZE);
    mSceneLayers[Land]->attachChild(std::move(laneNode4));

    std::unique_ptr<Lane> laneNode5(
        new Lane(Lane::Type::PavementBelow, Lane::Right, 100));
    laneNode5->setPosition(0, 5 * Constants::BLOCK_SIZE);
    mSceneLayers[Land]->attachChild(std::move(laneNode5));

    std::unique_ptr<Lane> laneNode6(
        new Lane(Lane::Type::Railway, Lane::Left, 100));
    laneNode6->setPosition(0, 6 * Constants::BLOCK_SIZE);
    mSceneLayers[Land]->attachChild(std::move(laneNode6));

    std::unique_ptr<Lane> laneNode7(
        new Lane(Lane::Type::RoadAbove, Lane::Right, 100));
    laneNode7->setPosition(0, 7 * Constants::BLOCK_SIZE);
    mSceneLayers[Land]->attachChild(std::move(laneNode7));

    std::unique_ptr<Lane> laneNode8(
        new Lane(Lane::Type::RoadMiddle, Lane::Left, 100));
    laneNode8->setPosition(0, 8 * Constants::BLOCK_SIZE);
    mSceneLayers[Land]->attachChild(std::move(laneNode8));

    std::unique_ptr<Lane> laneNode9(
        new Lane(Lane::Type::RoadBelow, Lane::Right, 100));
    laneNode9->setPosition(0, 9 * Constants::BLOCK_SIZE);
    mSceneLayers[Land]->attachChild(std::move(laneNode9));

    std::unique_ptr<Lane> laneNode10(
        new Lane(Lane::Type::RoadSingle, Lane::Left, 100));
    laneNode10->setPosition(0, 10 * Constants::BLOCK_SIZE);
    mSceneLayers[Land]->attachChild(std::move(laneNode10));

    std::unique_ptr<Character> character(new Character());
    character->setPosition(mSpawnPosition);
    mPlayerCharacter = character.get();
    mSceneLayers[Land]->attachChild(std::move(character));
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
