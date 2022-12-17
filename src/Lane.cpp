#include "Lane.hpp"

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <iostream>

#include "CommandQueue.hpp"
#include "Constants.hpp"
#include "DataTables.hpp"
#include "ResourceHolder.hpp"
#include "TexturesSingleton.hpp"
#include "Utility.hpp"
#include <algorithm>
#include <numeric>
#include <random>

namespace {
const std::vector<LaneData> Table = initializeLaneData();
}

Lane::Lane(Lane::Type type, Lane::Direction direction, float speed)
    : mType(type), mDirection(direction), mSpeed(speed) {
    mSprite = sf::Sprite(TexturesSingleton::getInstance().getTextures().get(
        Table[type].texture));

    switch (mType) {
        case Railway: {
            typeObstacles.push_back(Obstacle::Type::BlueBus);
            typeObstacles.push_back(Obstacle::Type::OrangeBus);
        }
            break;
        case RoadAbove:
        case RoadMiddle:
        case RoadBelow:
        case RoadSingle: {
            typeObstacles.push_back(Obstacle::Type::BlueCar);
            typeObstacles.push_back(Obstacle::Type::GrayCar);
            typeObstacles.push_back(Obstacle::Type::NewVan);
            typeObstacles.push_back(Obstacle::Type::OldVan);
            typeObstacles.push_back(Obstacle::Type::PoliceCar);
            typeObstacles.push_back(Obstacle::Type::RedCar);
            typeObstacles.push_back(Obstacle::Type::RedStripedCar);
            typeObstacles.push_back(Obstacle::Type::RedTruck);
            typeObstacles.push_back(Obstacle::Type::SchoolBus);
            typeObstacles.push_back(Obstacle::Type::WhiteTruck);
            typeObstacles.push_back(Obstacle::Type::YellowCab);
            typeObstacles.push_back(Obstacle::Type::YellowCar);
        }
            break;
        case PavementAbove:
        case PavementBelow: {
            typeObstacles.push_back(Obstacle::Type::FireHydrant);
        }
            break;
        case Grass: {
            typeObstacles.push_back(Obstacle::Type::Bush);
        }
            break;
        default: {
            typeObstacles.resize(0);
        }
    }

    if (isHavingStandingObstacle()) {

        std::vector<int> blocks(Constants::SCREEN_WIDTH / Constants::BLOCK_SIZE);
        std::iota(blocks.begin(), blocks.end(), 0);
        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(blocks.begin(), blocks.end(), g);
        blocks.resize(3);

        generateStandingObstacle(typeObstacles[0], blocks);
    }
}

void Lane::drawCurrent(sf::RenderTarget& target,
                       sf::RenderStates states) const {
    int numsOfBlocks = Constants::SCREEN_WIDTH / Constants::BLOCK_SIZE;

    for (int i = 0; i < numsOfBlocks; i++) {
        sf::Sprite laneSprite = mSprite;

        laneSprite.setPosition(i * Constants::BLOCK_SIZE, 0);
        target.draw(laneSprite, states);
    }
}

void Lane::updateCurrent(sf::Time dt, CommandQueue& commands) {
    //check type of lane
    if (isStaticLane()) return;
    if (isHavingStandingObstacle()) return;

    // Generate new obstacles
    generateMovingObstacle(dt);
}

unsigned int Lane::getCategory() const {
    return Category::Lane;
}

void Lane::generateMovingObstacle(sf::Time dt) {
    int tmp = randomInt(1000);
    if (tmp >= 10) return;

    int index = randomInt(typeObstacles.size());
    Obstacle::Type obstacleType = typeObstacles[index];

    auto children = this->getChildren();
    auto lastObstacle = children.empty() ? nullptr : children.back();

    if (mDirection == Lane::Left) {
        std::unique_ptr<Obstacle> obstacle(
            new Obstacle(obstacleType, Obstacle::Direction::Left));

        if (lastObstacle) {
            float end = lastObstacle->getPosition().x +
                        lastObstacle->getBoundingRect().width;

            if (end > Constants::SCREEN_WIDTH) return;
        }
        
        obstacle->setPosition(Constants::SCREEN_WIDTH, mSprite.getPosition().y);
        obstacle->setVelocity(mDirection * mSpeed, 0.f);
        attachChild(std::move(obstacle));
    }

    if (mDirection == Lane::Right) {
        std::unique_ptr<Obstacle> obstacle(
            new Obstacle(obstacleType, Obstacle::Direction::Right));

        if (lastObstacle) {
            float start = lastObstacle->getPosition().x;
            if (start < 0) return;
        }

        obstacle->setPosition(-obstacle->getBoundingRect().width,
                              mSprite.getPosition().y);
        obstacle->setVelocity(mDirection * mSpeed, 0.f);

        attachChild(std::move(obstacle));
    }
}

void Lane::generateStandingObstacle(Obstacle::Type obstacleType,
                                    std::vector<int>& blocks) {
    mSpeed = 0.0;
    for (auto x : blocks) {
        std::unique_ptr<Obstacle> obstacle(
            new Obstacle(obstacleType, Obstacle::Direction::Left));
        obstacle->setPosition(x*Constants::BLOCK_SIZE, mSprite.getPosition().y);
        obstacle->setVelocity(mDirection * mSpeed, 0.f);
        attachChild(std::move(obstacle));
    }
}

bool Lane::isStaticLane() const{
    if (mType == Lane::Type::LilyPadAbove ||
        mType == Lane::Type::LilyPadBelow ||
        mType == Lane::Type::LilyPadSingle) {
        return true;
    }
    return false;
}

bool Lane::isHavingStandingObstacle() const {
    if (mType == Lane::PavementAbove ||
        mType == Lane::PavementBelow ||
        mType == Lane::Grass) {
        return true;
    }
    return false;
}