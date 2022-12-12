#include "Obstacle.hpp"

#include "ResourceHolder.hpp"
#include "TexturesSingleton.hpp"
#include "Utility.hpp"
#include "DataTables.hpp"

namespace {
    const std::vector<ObstacleData> Table = initializeObstacleData();
}

Obstacle::Obstacle(Type type, Direction direction)
    : mType(type){
    if (direction == Left) {
        mSprite = sf::Sprite(TexturesSingleton::getInstance().getTextures().get(
            Table[(unsigned)type].texture));
    }
    else{
        mSprite = sf::Sprite(TexturesSingleton::getInstance().getTextures().get(
            Table[(unsigned)type + (unsigned)Obstacle::Type::TypeCount].texture));
    }
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