#include "World.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <algorithm>
#include <cmath>
#include <limits>
#include <random>

#include "Constants.hpp"
#include "TexturesSingleton.hpp"

World::World(sf::RenderWindow& window, FontHolder& fonts)
    : 
    mWindow(window),
    mWorldView(window.getDefaultView()),
    mFonts(fonts),
    mSceneGraph(),
    mSceneLayers(),
    mWorldBounds(0.f, 0.f, mWorldView.getSize().x + 400,
        mWorldView.getSize().y),
    mSpawnPosition(Constants::BLOCK_SIZE * 8 + Constants::BLOCK_SIZE / 2,
        Constants::LANE_HEIGHT / 2.f),
    mViewPosition(mWorldView.getSize().x / 2.f, mWorldView.getSize().y / 2.f),
    mPlayerCharacter(nullptr),
    mLevel(nullptr)
{
    loadTextures();
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

#include <iostream>

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

    //level setup start here
    if (mLevel == nullptr)
    {
        mLevel = std::unique_ptr<Level>(new Level(1));
    }
    else {
        mLevel->levelUp();
    }
    loadLevel();
    //level startup end here

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

void World::loadLevel()
{
    float speed = mLevel.get()->caculateSpeed();
    int spawnRate = mLevel.get()->caculateSpawnRate();

    /*std::unique_ptr<Lane> laneNode1(
        new Lane(Lane::Type::LilyPadAbove, Lane::Right, speed));
    laneNode1->setPosition(0, 1 * Constants::BLOCK_SIZE);
    laneNode1.get()->setSpawnRate(spawnRate);
    mSceneLayers[Land]->attachChild(std::move(laneNode1));

    std::unique_ptr<Lane> laneNode2(
        new Lane(Lane::Type::LilyPadBelow, Lane::Left, speed));
    laneNode2->setPosition(0, 2 * Constants::BLOCK_SIZE);
    laneNode2.get()->setSpawnRate(spawnRate);
    mSceneLayers[Land]->attachChild(std::move(laneNode2));

    std::unique_ptr<Lane> laneNode3(
        new Lane(Lane::Type::LilyPadSingle, Lane::Right, speed));
    laneNode3->setPosition(0, 3 * Constants::BLOCK_SIZE);
    laneNode3.get()->setSpawnRate(spawnRate);
    mSceneLayers[Land]->attachChild(std::move(laneNode3));

    std::unique_ptr<Lane> laneNode4(
        new Lane(Lane::Type::PavementAbove, Lane::Left, speed));
    laneNode4->setPosition(0, 4 * Constants::BLOCK_SIZE);
    laneNode4.get()->setSpawnRate(spawnRate);
    mSceneLayers[Land]->attachChild(std::move(laneNode4));

    std::unique_ptr<Lane> laneNode5(
        new Lane(Lane::Type::PavementBelow, Lane::Right, speed));
    laneNode5->setPosition(0, 5 * Constants::BLOCK_SIZE);
    laneNode5.get()->setSpawnRate(spawnRate);
    mSceneLayers[Land]->attachChild(std::move(laneNode5));

    std::unique_ptr<Lane> laneNode6(
        new Lane(Lane::Type::Railway, Lane::Left, speed));
    laneNode6->setPosition(0, 6 * Constants::BLOCK_SIZE);
    laneNode6.get()->setSpawnRate(spawnRate);
    mSceneLayers[Land]->attachChild(std::move(laneNode6));

    std::unique_ptr<Lane> laneNode7(
        new Lane(Lane::Type::RoadAbove, Lane::Right, speed));
    laneNode7->setPosition(0, 7 * Constants::BLOCK_SIZE);
    laneNode7.get()->setSpawnRate(spawnRate);
    mSceneLayers[Land]->attachChild(std::move(laneNode7));

    std::unique_ptr<Lane> laneNode8(
        new Lane(Lane::Type::RoadMiddle, Lane::Left, speed));
    laneNode8->setPosition(0, 8 * Constants::BLOCK_SIZE);
    laneNode8.get()->setSpawnRate(spawnRate);
    mSceneLayers[Land]->attachChild(std::move(laneNode8));

    std::unique_ptr<Lane> laneNode9(
        new Lane(Lane::Type::RoadBelow, Lane::Right, speed));
    laneNode9->setPosition(0, 9 * Constants::BLOCK_SIZE);
    laneNode9.get()->setSpawnRate(spawnRate);
    mSceneLayers[Land]->attachChild(std::move(laneNode9));

    std::unique_ptr<Lane> laneNode10(
        new Lane(Lane::Type::RoadSingle, Lane::Left, speed));
    laneNode10->setPosition(0, 10 * Constants::BLOCK_SIZE);
    laneNode10.get()->setSpawnRate(spawnRate);
    mSceneLayers[Land]->attachChild(std::move(laneNode10));*/

    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(1, 11);
    std::uniform_int_distribution<std::mt19937::result_type> clmm(0, 1);
    /*for (int i = 0;i <= 10;++i)
    {
        int theChosenOne = dist(rng);
        if (theChosenOne <= 4) {
            Lane::Type tem;
            switch (theChosenOne)
            {
            case 1:
                tem = Lane::Grass;
                break;
            case 2:
                tem = Lane::LilyPadSingle;
                break;
            case 3:
                tem = Lane::Railway;
                break;
            case 4:
                tem = Lane::RoadSingle;
                break;
            default:
                break;
            }
            std::unique_ptr<Lane> laneNode(new Lane(tem, Lane::Left, speed));
            laneNode->setPosition(0, i * Constants::BLOCK_SIZE);
            laneNode.get()->setSpawnRate(spawnRate);
            mSceneLayers[Land]->attachChild(std::move(laneNode));
        }
        else if (theChosenOne >= 5 && theChosenOne <= 7 && i <= 9) {
            Lane::Type temA, temB;
            switch (theChosenOne)
            {
            case 5:
                temA = Lane::LilyPadAbove;
                temB = Lane::LilyPadBelow;
                break;
            case 6:
                temA = Lane::PavementAbove;
                temB = Lane::PavementBelow;
                break;
            case 7:
                temA = Lane::RoadAbove;
                temB = Lane::RoadBelow;
                break;
            default:
                break;
            }
            std::unique_ptr<Lane> laneNodeA(
                new Lane(temA, Lane::Right, speed));
            laneNodeA->setPosition(0, i * Constants::BLOCK_SIZE);
            laneNodeA.get()->setSpawnRate(spawnRate);
            mSceneLayers[Land]->attachChild(std::move(laneNodeA));
            ++i;
            std::unique_ptr<Lane> laneNodeB(
                new Lane(temB, Lane::Left, speed));
            laneNodeB->setPosition(0, i * Constants::BLOCK_SIZE);
            laneNodeB.get()->setSpawnRate(spawnRate);
            mSceneLayers[Land]->attachChild(std::move(laneNodeB));
        }
        else if (theChosenOne == 8 && i <= 8) {
            Lane::Type temA, temB, temC;
            switch (theChosenOne)
            {
            case 8:
                temA = Lane::RoadAbove;
                temB = Lane::RoadMiddle;
                temC = Lane::RoadBelow;
                break;
            default:
                break;
            }
            std::unique_ptr<Lane> laneNodeA(
                new Lane(temA, Lane::Right, speed));
            laneNodeA->setPosition(0, i * Constants::BLOCK_SIZE);
            laneNodeA.get()->setSpawnRate(spawnRate);
            mSceneLayers[Land]->attachChild(std::move(laneNodeA));
            ++i;
            std::unique_ptr<Lane> laneNodeB(
                new Lane(temB, Lane::Left, speed));
            laneNodeB->setPosition(0, i * Constants::BLOCK_SIZE);
            laneNodeB.get()->setSpawnRate(spawnRate);
            mSceneLayers[Land]->attachChild(std::move(laneNodeB));
            ++i;
            std::unique_ptr<Lane> laneNodeC(
                new Lane(temC, Lane::Left, speed));
            laneNodeC->setPosition(0, i * Constants::BLOCK_SIZE);
            laneNodeC.get()->setSpawnRate(spawnRate);
            mSceneLayers[Land]->attachChild(std::move(laneNodeC));
        }
        else {
            --i;
        }
    }*/

    int current = dist(rng),last;
    for (int i = 0;i < 11;++i)
    {
        std::cout << current << "\n";
        last = current;
        Lane::Type tem;
        switch (current)
        {
        case 1:
            tem = Lane::Grass;
            break;
        case 2:
            tem = Lane::LilyPadSingle;
            break;
        case 3:
            tem = Lane::Railway;
            break;
        case 4:
            tem = Lane::RoadSingle;
            break;
        case 5:
            tem = Lane::LilyPadAbove;
            break;
        case 6:
            tem = Lane::PavementAbove;
            break;
        case 7:
            tem = Lane::RoadAbove;
            break;
        case 8:
            tem = Lane::LilyPadBelow;
            break;
        case 9:
            tem = Lane::PavementBelow;
            break;
        case 10:
            tem = Lane::RoadMiddle;
            break;
        case 11:
            tem = Lane::RoadBelow;
            break;
        default:
            break;
        }

        Lane::Direction dt;
        if (clmm(rng) == 0) {
            dt = Lane::Left;
        }
        else {
            dt = Lane::Right;
        }
        std::unique_ptr<Lane> laneNodeA(new Lane(tem, dt, speed));
        laneNodeA->setPosition(0, i * Constants::BLOCK_SIZE);
        laneNodeA.get()->setSpawnRate(spawnRate);
        mSceneLayers[Land]->attachChild(std::move(laneNodeA));

        
        if (last == 5) {
            current = 8;
        }
        else if (last == 6) {
            current = 9;
        }
        else if (last == 10) {
            current = 11;
        }
        else if (last == 7) {
            if (i <= 8) {
                if (clmm(rng) == 0) { current = 10; }
                else { current = 11; }
            }
            else { current = 11; }
        }
        else{
            while (current == last || 
                current >= 8 || 
                (i >= 10 && current >= 5)||
                (i>=9&&current==7)||
                (last==9&&current==6)||
                (last==11&&current==7)||
                ((last==2||last==8)&&(current==5||current==2))
                ) {
                current = dist(rng);
            }
        }
    }
}
