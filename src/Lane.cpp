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

#include <iostream>

Lane::Lane(Lane::Type type, Lane::Direction direction, float speed,
           TrafficLight* trafficLight)
    : mType(type),
      mDirection(direction),
      mSpeed(speed),
      mTrafficLight(trafficLight) {
    mSprite = sf::Sprite(TexturesSingleton::getInstance().getTextures().get(
        Table[type].texture));

    maxSpeed = mSpeed;

    if (mTrafficLight) {
        updateSpeed();
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

    if (mTrafficLight) {
        updateSpeed();
    }
}

void Lane::updateSpeed() {
    if (mTrafficLight->getState() == TrafficLight::State::Red) {
        mSpeed = 0;
    } else if (mTrafficLight->getState() == TrafficLight::State::Yellow) {
        mSpeed = maxSpeed / 2;
    } else if (mTrafficLight->getState() == TrafficLight::State::Green) {
        mSpeed = maxSpeed;
    }
    auto children = this->getChildren();
    for (SceneNode* each : children) {
        Obstacle* obstacle = dynamic_cast<Obstacle*>(each);
        if (obstacle != nullptr) {
            obstacle->setVelocity(mDirection * mSpeed, 0.f);
        }
    }
}

unsigned int Lane::getCategory() const {
    return Category::Lane;
}

void Lane::generateObstacle(sf::Time dt) {
    if (mSpeed != maxSpeed) return;
    int tmp = randomInt(10000);
    if (tmp >= 30) return;

    auto obstacleType = Obstacle::getRandomObstacleType();
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
