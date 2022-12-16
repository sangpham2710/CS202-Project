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
        case RoadBelow: {
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
        default: {
            typeObstacles.resize(0);
        }
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
    // Generate new obstacles
    generateObstacle(dt);
}

unsigned int Lane::getCategory() const {
    return Category::Lane;
}

void Lane::generateObstacle(sf::Time dt) {
    if (typeObstacles.empty()) return;

    int tmp = randomInt(1000);
    if (tmp >= 10) return;

    auto obstacleType = Obstacle::getRandomObstacleType();
    while (std::find(typeObstacles.begin(), typeObstacles.end(), obstacleType)
        == typeObstacles.end()) {
        obstacleType = Obstacle::getRandomObstacleType();
    }

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
