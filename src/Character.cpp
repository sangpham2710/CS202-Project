#include "Character.hpp"

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include "CommandQueue.hpp"
#include "ResourceHolder.hpp"
#include "TexturesSingleton.hpp"
#include "Utility.hpp"

Character::Character(): mSprite(TexturesSingleton::getInstance().getTextures().get(Textures::CharacterDown)),
                        mIsMarkedForRemoval(false)
{
    mAnimation.setTexture(TexturesSingleton::getInstance().getTextures().get(Textures::CharacterDown));
    mAnimation.setFrameSize(sf::Vector2i(64,64));
    mAnimation.setNumFrames(4);
    mAnimation.setRepeating(1);
    mAnimation.setDuration(sf::seconds(1));
    mAnimation.setPosition(-32, -32);
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
    target.draw(mAnimation, states);
}

void Character::updateCurrent(sf::Time dt, CommandQueue& commands) {
    Entity::updateCurrent(dt, commands);
    mAnimation.update(dt);
}

void Character::setAnimation(int type) {
    switch (type)
    {
    case 0://up
        mAnimation.setTexture(TexturesSingleton::getInstance().getTextures().get(Textures::CharacterUp));
        break;
    case 1://down
        mAnimation.setTexture(TexturesSingleton::getInstance().getTextures().get(Textures::CharacterDown));
        break;
    case 2://left
        mAnimation.setTexture(TexturesSingleton::getInstance().getTextures().get(Textures::CharacterLeft));
        break;
    case 3://right
        mAnimation.setTexture(TexturesSingleton::getInstance().getTextures().get(Textures::CharacterRight));
        break;
    default:
        break;
    }
}