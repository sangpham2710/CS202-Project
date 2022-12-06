#include "Lane.hpp"

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include "CommandQueue.hpp"
#include "Constants.hpp"
#include "ResourceHolder.hpp"
#include "Utility.hpp"

Lane::Lane(Type type, Direction direction, float speed,
           const TextureHolder& textures)
    : mType(type), mDirection(direction), mSpeed(speed), mTextures(textures) {
    const sf::Texture& texture = mTextures.get(Textures::BlueBusLeft);

    mSprite.setTexture(texture);
    sf::IntRect textureRect(0, 0, Constants::LANE_WIDTH,
                            Constants::LANE_HEIGHT);
    mSprite.setTextureRect(textureRect);
    centerOrigin(mSprite);
}

void Lane::drawCurrent(sf::RenderTarget& target,
                       sf::RenderStates states) const {
    target.draw(mSprite, states);
}

void Lane::updateCurrent(sf::Time dt, CommandQueue& commands) {
    // Move obstacles
    moveObstacles(dt);

    // Generate new obstacles
    generateObstacle(dt);
}

void Lane::generateObstacle(sf::Time dt) {
    int tmp = randomInt(100);
    if (tmp < 10) {
        std::unique_ptr<Obstacle> obstacle(
            new Obstacle(Obstacle::BlueBusLeft, mTextures));
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