#include "Lane.hpp"

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <iostream>

#include "CommandQueue.hpp"
#include "Constants.hpp"
#include "ResourceHolder.hpp"
#include "TexturesSingleton.hpp"
#include "Utility.hpp"


Lane::Lane(Lane::Type type, Lane::Direction direction, float speed)
    : mType(type), mDirection(direction), mSpeed(speed) {
    switch (type) {
        case RoadSingle: {
            mSprite =
                sf::Sprite(TexturesSingleton::getInstance().getTextures().get(
                    Textures::RoadSingle));
        } break;
        case PavementAbove: {
            mSprite =
                sf::Sprite(TexturesSingleton::getInstance().getTextures().get(
                    Textures::PavementAbove));
        } break;
        case Grass: {
            mSprite =
                sf::Sprite(TexturesSingleton::getInstance().getTextures().get(
                    Textures::GrassLane));
        }
    }
}

void Lane::drawCurrent(sf::RenderTarget& target,
                       sf::RenderStates states) const {
    target.draw(mSprite, states);

    int numsOfBlocks = Constants::SCREEN_WIDTH / Constants::BLOCK_SIZE;

    for (int i = 1; i < numsOfBlocks; i++) {
        sf::Sprite addLane = mSprite;

        addLane.setPosition(i * Constants::BLOCK_SIZE, this->getPosition().y);
        target.draw(addLane);
    }
}

void Lane::updateCurrent(sf::Time dt, CommandQueue& commands) {
    // Move obstacles
    // moveObstacles(dt);

    // Delete obstacles out of view
    // deleteObstacle(dt);

    // Generate new obstacles
    generateObstacle(dt);
}

unsigned int Lane::getCategory() const {
    return Category::Lane;
}


void Lane::generateObstacle(sf::Time dt) {
    int tmp = randomInt(1000);
    if (tmp < 10) {
        if (mDirection == Lane::Left) {
            std::unique_ptr<Obstacle> obstacle(
                new Obstacle(Obstacle::SchoolBusRight));
            obstacle->setPosition(Constants::SCREEN_WIDTH,
                                  mSprite.getPosition().y);
            obstacle->setVelocity(mDirection * mSpeed, 0.f);
            attachChild(std::move(obstacle));
        } else if (mDirection == Lane::Right) {
            std::unique_ptr<Obstacle> obstacle(
                new Obstacle(Obstacle::SchoolBusRight));
            obstacle->setPosition(0, mSprite.getPosition().y);
            obstacle->setVelocity(mDirection * mSpeed, 0.f);
            attachChild(std::move(obstacle));
        }
    }
}
