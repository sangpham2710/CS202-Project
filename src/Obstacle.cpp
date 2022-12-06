#include "Obstacle.hpp"

#include "ResourceHolder.hpp"
#include "Utility.hpp"


Obstacle::Obstacle(Type type, const TextureHolder& textures)
    : mType(type), mSprite(textures.get(Textures::BlueBusLeft)) {
    centerOrigin(mSprite);
}

sf::FloatRect Obstacle::getBoundingRect() const {
    return getWorldTransform().transformRect(mSprite.getGlobalBounds());
}

void Obstacle::drawCurrent(sf::RenderTarget& target,
                           sf::RenderStates states) const {
    target.draw(mSprite, states);
}

unsigned int Obstacle::getCategory() const {
    return Category::Obstacle;
}