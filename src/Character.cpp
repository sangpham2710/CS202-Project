#include "Character.hpp"

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include "CommandQueue.hpp"
#include "ResourceHolder.hpp"
#include "TexturesSingleton.hpp"
#include "Utility.hpp"

Character::Character() :
    mAnimation(TexturesSingleton::getInstance().getTextures().get(Textures::CharacterExplosion))
{
    mSprite.setTexture(TexturesSingleton::getInstance().getTextures().get(Textures::CharacterDown));

    mAnimation.setFrameSize(sf::Vector2i(256, 256));
    mAnimation.setNumFrames(16);
    mAnimation.setDuration(sf::seconds(1));
    mAnimation.setRepeating(1);

    mAnimation.setPosition(-31,-31);
    mAnimation.setScale(0.251, 0.251);

    mIsMarkedForRemoval=false;
    isDead = 0;
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

void Character::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const {
    if (isDead) {
        target.draw(mAnimation,states);
    }
    else {
        target.draw(mSprite, states);
    }
}

void Character::updateCurrent(sf::Time dt, CommandQueue& commands) {
    Entity::updateCurrent(dt, commands);
    if (characterClock.getElapsedTime().asSeconds() > 3.0) {
        isDead = 1;
    }
    if (characterClock.getElapsedTime().asSeconds() > 6.0) {
        isDead = 0;
        characterClock.restart();
    }
    if (isDead) {
        mAnimation.update(dt);
        return;
    }
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
