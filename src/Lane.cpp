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
    : mType(type),
      mDirection(direction),
      mSpeed(speed),
      mSprite(TexturesSingleton::getInstance().getTextures().get(
          Textures::GrassLane)) {
}

void Lane::drawCurrent(sf::RenderTarget& target,
                       sf::RenderStates states) const {
    target.draw(mSprite, states);
}

void Lane::updateCurrent(sf::Time dt, CommandQueue& commands) {
    // Move obstacles
    // moveObstacles(dt);

    // Generate new obstacles
    // generateObstacle(dt);
}

unsigned int Lane::getCategory() const {
    return Category::RoadLayer;
}

bool Lane::isDestroyed() const
{
    return false;
}

void Lane::generateObstacle(sf::Time dt) {
    int tmp = randomInt(100);
    if (tmp < 10) {
        std::unique_ptr<Obstacle> obstacle(new Obstacle(Obstacle::BlueBusLeft));
        obstacle->setPosition(0, 0);
        mObstacles.push_back(obstacle.get());
        attachChild(std::move(obstacle));
    }
}

void Lane::moveObstacles(sf::Time dt) {
    for (auto& obstacle : mObstacles) {
        obstacle->move(mDirection * mSpeed * dt.asSeconds(), 0.f);
    }
}