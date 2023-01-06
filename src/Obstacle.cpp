#include "Obstacle.hpp"

#include "Constants.hpp"
#include "DataTables.hpp"
#include "ResourceHolder.hpp"
#include "TexturesSingleton.hpp"
#include "Utility.hpp"

namespace {
const std::vector<ObstacleData> Table = initializeObstacleData();
}

Obstacle::Obstacle(Type type, Direction direction) : mType(type) {
    if (direction == Direction::Left) {
        mSprite = sf::Sprite(TexturesSingleton::getInstance().getTextures().get(
            Table[(unsigned)type].texture));
    } else {
        mSprite = sf::Sprite(TexturesSingleton::getInstance().getTextures().get(
            Table[(unsigned)type + (unsigned)Obstacle::Type::TypeCount]
                .texture));
    }
}

sf::FloatRect Obstacle::getBoundingRect() const {
    auto rect = getWorldTransform().transformRect(mSprite.getGlobalBounds());
    rect.left += Constants::OBSTACLE_HITBOX_HEIGHT_OFFSET / 2;
    rect.top += Constants::OBSTACLE_HITBOX_WIDTH_OFFSET / 2;
    rect.width -= Constants::OBSTACLE_HITBOX_HEIGHT_OFFSET;
    rect.height -= Constants::OBSTACLE_HITBOX_WIDTH_OFFSET;
    return rect;
}

void Obstacle::setTextureWrecked() {
    // mSprite.setColor(sf::Color(255, 255, 255, 128));
}

void Obstacle::drawCurrent(sf::RenderTarget& target,
                           sf::RenderStates states) const {
    target.draw(mSprite, states);
}

unsigned int Obstacle::getCategory() const {
    return Category::Obstacle;
}
