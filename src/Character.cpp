#include "Character.hpp"

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include "CommandQueue.hpp"
#include "Constants.hpp"
#include "ResourceHolder.hpp"
#include "TexturesSingleton.hpp"
#include "Utility.hpp"

Character::Character() : mIsMarkedForRemoval(false), mIsMoving(false) {
    mAnimation.setTexture(TexturesSingleton::getInstance().getTextures().get(
        Textures::CharacterDown));
    mAnimation.setFrameSize(sf::Vector2i(64, 64));
    mAnimation.setNumFrames(4);
    mAnimation.setDuration(sf::seconds(Constants::MOVE_ANIMATION_DURATION));
    mAnimation.restart();
    centerOrigin(mAnimation);
}

unsigned int Character::getCategory() const {
    return Category::PlayerCharacter;
}

sf::FloatRect Character::getBoundingRect() const {
    return getWorldTransform().transformRect(mAnimation.getGlobalBounds());
}

bool Character::isMarkedForRemoval() const {
    return mIsMarkedForRemoval;
}

void Character::drawCurrent(sf::RenderTarget& target,
                            sf::RenderStates states) const {
    target.draw(mAnimation, states);
}

void Character::updateCurrent(sf::Time dt, CommandQueue& commands) {
    if (mIsMoving) mAnimation.update(dt);
    if (mAnimation.isFinished()) {
        this->setVelocity(0.0f, 0.0f);
        mIsMoving = false;
        mAnimation.restart();
    }
    Entity::updateCurrent(dt, commands);
}

bool Character::isMoving() const {
    return mIsMoving;
}

void Character::moveUp() {
    if (mIsMoving == true) return;
    mIsMoving = true;
    float velocityX = 0.0f;
    float velocityY = -Constants::BLOCK_SIZE;
    this->setVelocity(velocityX / Constants::MOVE_ANIMATION_DURATION,
                      velocityY / Constants::MOVE_ANIMATION_DURATION);
    mAnimation.setTexture(TexturesSingleton::getInstance().getTextures().get(
        Textures::CharacterUp));
}

void Character::moveDown() {
    if (mIsMoving == true) return;
    mIsMoving = true;
    float velocityX = 0.0f;
    float velocityY = Constants::BLOCK_SIZE;
    this->setVelocity(velocityX / Constants::MOVE_ANIMATION_DURATION,
                      velocityY / Constants::MOVE_ANIMATION_DURATION);

    mAnimation.setTexture(TexturesSingleton::getInstance().getTextures().get(
        Textures::CharacterDown));
}

void Character::moveLeft() {
    if (mIsMoving == true) return;
    mIsMoving = true;
    float velocityX = -Constants::BLOCK_SIZE;
    float velocityY = 0.0f;
    this->setVelocity(velocityX / Constants::MOVE_ANIMATION_DURATION,
                      velocityY / Constants::MOVE_ANIMATION_DURATION);
    mAnimation.setTexture(TexturesSingleton::getInstance().getTextures().get(
        Textures::CharacterLeft));
}

void Character::moveRight() {
    if (mIsMoving == true) return;
    mIsMoving = true;
    float velocityX = Constants::BLOCK_SIZE;
    float velocityY = 0.0f;
    this->setVelocity(velocityX / Constants::MOVE_ANIMATION_DURATION,
                      velocityY / Constants::MOVE_ANIMATION_DURATION);
    mAnimation.setTexture(TexturesSingleton::getInstance().getTextures().get(
        Textures::CharacterRight));
}