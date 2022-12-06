#pragma once

#include <SFML/Graphics/Sprite.hpp>

#include "Entity.hpp"
#include "Obstacle.hpp"
#include "ResourceIdentifiers.hpp"

class Lane : public Entity {
   public:
    // Type
    enum Type {
        Grass,
        Pavement,
        Road,
    };

    // Direction of obstacles
    enum Direction {
        Left = -1,
        NoDirection = 0,
        Right = 1,
    };

    Lane::Lane(Type type, Direction direction, float speed,
               const TextureHolder& textures);

   private:
    virtual void drawCurrent(sf::RenderTarget& target,
                             sf::RenderStates states) const;
    virtual void updateCurrent(sf::Time dt, CommandQueue& commands);

    void generateObstacle(sf::Time dt);
    void moveObstacles(sf::Time dt);

    Type mType;
    Direction mDirection;
    float mSpeed;
    sf::Sprite mSprite;
    std::vector<Obstacle*> mObstacles;
    const TextureHolder& mTextures;
};