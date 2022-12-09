#include "Character.hpp"

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include "CommandQueue.hpp"
#include "ResourceHolder.hpp"
#include "TexturesSingleton.hpp"
#include "Utility.hpp"

Character::Character() :
    mAnimation(TexturesSingleton::getInstance().getTextures().get(Textures::CharacterDown))
{
    mSprite.setScale(sf::Vector2f(0.3, 0.3));
    mSprite.setTexture(TexturesSingleton::getInstance().getTextures().get(Textures::CharacterDown));
    mAnimation.setFrameSize(sf::Vector2i(256, 256));
    mAnimation.setNumFrames(16);
    mAnimation.setDuration(sf::seconds(1));

    mIsMarkedForRemoval=false;
    centerOrigin(mSprite);
}

unsigned int Character::getCategory() const {
    return Category::PlayerCharacter;
}

sf::FloatRect Character::getBoundingRect() const {
    return getWorldTransform().transformRect(mSprite.getGlobalBounds());
}

bool Character::isMarkedForRemoval() const {
    return mIsMarkedForRemoval;
}

void Character::drawCurrent(sf::RenderTarget& target,
                            sf::RenderStates states) const {
    target.draw(mSprite, states);
}

void Character::updateCurrent(sf::Time dt, CommandQueue& commands) {
    Entity::updateCurrent(dt, commands);
}

void Character::moveUpAnimation() {
    mSprite.setTexture(TexturesSingleton::getInstance().getTextures().get(Textures::CharacterUp));
}

void Character::moveDownAnimation() {
    mSprite.setTexture(TexturesSingleton::getInstance().getTextures().get(Textures::CharacterDown));
}

void Character::moveLeftAnimation() {
    mSprite.setTexture(TexturesSingleton::getInstance().getTextures().get(Textures::CharacterLeft));
}

void Character::moveRightAnimation() {
    mSprite.setTexture(TexturesSingleton::getInstance().getTextures().get(Textures::CharacterRight));
}

void Character::drawCurrent(sf::RenderTarget& target,sf::RenderStates states) const {
        target.draw(mAnimation, states);
}