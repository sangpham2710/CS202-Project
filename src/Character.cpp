#include "Character.hpp"

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include "CommandQueue.hpp"
#include "ResourceHolder.hpp"
#include "TexturesSingleton.hpp"
#include "Utility.hpp"

Character::Character()
    : mSprite(TexturesSingleton::getInstance().getTextures().get(
          Textures::CharacterDown)),
      mIsMarkedForRemoval(false) {
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