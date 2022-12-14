#include "Character.hpp"

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include "CommandQueue.hpp"
#include "Constants.hpp"
#include "ResourceHolder.hpp"
#include "TexturesSingleton.hpp"
#include "Utility.hpp"

namespace {
    const std::vector<characterData> Table = initializeCharacterData();
}

Character::Character(int type) : mIsMoving(false), mShowExplosion(true), mType(type) {
    mAnimation.setTexture(TexturesSingleton::getInstance().getTextures().get(
        Table[mType * (unsigned)Character::Direction::TypeCount + (unsigned)Character::Direction::CharacterDown].texture));
    mAnimation.setFrameSize(sf::Vector2i(64, 64));
    mAnimation.setNumFrames(4);
    mAnimation.setDuration(sf::seconds(Constants::MOVE_ANIMATION_DURATION));
    mAnimation.restart();
    centerOrigin(mAnimation);
    mExplosion.setTexture(TexturesSingleton::getInstance().getTextures().get(
        Textures::Explosion));
    mExplosion.setFrameSize(sf::Vector2i(256, 256));
    mExplosion.setNumFrames(16);
    mExplosion.setDuration(sf::seconds(1));
    centerOrigin(mExplosion);
}

unsigned int Character::getCategory() const {
    return Category::PlayerCharacter;
}

sf::FloatRect Character::getBoundingRect() const {
    auto rect = getWorldTransform().transformRect(mAnimation.getGlobalBounds());
    rect.left -= Constants::BLOCK_SIZE / 2;
    rect.top -= Constants::BLOCK_SIZE / 2;
    rect.left += (Constants::BLOCK_SIZE - Constants::HITBOX_SIZE) / 2;
    rect.top += (Constants::BLOCK_SIZE - Constants::HITBOX_SIZE) / 2;
    rect.width = Constants::HITBOX_SIZE;
    rect.height = Constants::HITBOX_SIZE;
    return rect;
}

bool Character::isMarkedForRemoval() const {
    return isDestroyed() && (mExplosion.isFinished() || !mShowExplosion);
}

void Character::drawCurrent(sf::RenderTarget& target,
                            sf::RenderStates states) const {
    if (isDestroyed() && mShowExplosion) {
        target.draw(mExplosion, states);
        target.draw(mAnimation, states);
    } else {
        target.draw(mAnimation, states);
    }
}

void Character::updateCurrent(sf::Time dt, CommandQueue& commands) {
    if (isDestroyed()) {
        mExplosion.update(dt);
        return;
    }
    if (mIsMoving) mAnimation.update(dt);
    if (mAnimation.isFinished()) {
        mIsMoving = false;
        setVelocity(0.0f, 0.0f);
        setPosition(floor(getPosition().x / Constants::BLOCK_SIZE) *
                            Constants::BLOCK_SIZE +
                        Constants::BLOCK_SIZE / 2,
                    floor(getPosition().y / Constants::BLOCK_SIZE) *
                            Constants::BLOCK_SIZE +
                        Constants::BLOCK_SIZE / 2);
        mAnimation.restart();
    }
    Entity::updateCurrent(dt, commands);
}

bool Character::isMoving() const {
    return mIsMoving;
}

void Character::setTextureWrecked() {
    mAnimation.setColor(sf::Color(255, 255, 255, 128));
}

void Character::setExplosionPosition(sf::Vector2f position) {
    mExplosion.setPosition(position);
}

void Character::moveUp() {
    if (mIsMoving == true) return;
    mIsMoving = true;
    float velocityX = 0.0f;
    float velocityY = -Constants::BLOCK_SIZE;
    this->setVelocity(velocityX / Constants::MOVE_ANIMATION_DURATION,
                      velocityY / Constants::MOVE_ANIMATION_DURATION);
    mAnimation.setTexture(TexturesSingleton::getInstance().getTextures().get(
        Table[mType * (unsigned)Character::Direction::TypeCount + 
                      (unsigned)Character::Direction::CharacterUp].texture));
}

void Character::moveDown() {
    if (mIsMoving == true) return;
    mIsMoving = true;
    float velocityX = 0.0f;
    float velocityY = Constants::BLOCK_SIZE;
    this->setVelocity(velocityX / Constants::MOVE_ANIMATION_DURATION,
                      velocityY / Constants::MOVE_ANIMATION_DURATION);

    mAnimation.setTexture(TexturesSingleton::getInstance().getTextures().get(
        Table[mType * (unsigned)Character::Direction::TypeCount + 
                      (unsigned)Character::Direction::CharacterDown].texture));
}

void Character::moveLeft() {
    if (mIsMoving == true) return;
    mIsMoving = true;
    float velocityX = -Constants::BLOCK_SIZE;
    float velocityY = 0.0f;
    this->setVelocity(velocityX / Constants::MOVE_ANIMATION_DURATION,
                      velocityY / Constants::MOVE_ANIMATION_DURATION);
    mAnimation.setTexture(TexturesSingleton::getInstance().getTextures().get(
        Table[mType * (unsigned)Character::Direction::TypeCount + 
                      (unsigned)Character::Direction::CharacterLeft].texture));
}

void Character::moveRight() {
    if (mIsMoving == true) return;
    mIsMoving = true;
    float velocityX = Constants::BLOCK_SIZE;
    float velocityY = 0.0f;
    this->setVelocity(velocityX / Constants::MOVE_ANIMATION_DURATION,
                      velocityY / Constants::MOVE_ANIMATION_DURATION);
    mAnimation.setTexture(TexturesSingleton::getInstance().getTextures().get(
        Table[mType * (unsigned)Character::Direction::TypeCount + 
                      (unsigned)Character::Direction::CharacterRight].texture));
}