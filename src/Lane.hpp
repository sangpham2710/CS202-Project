#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include <vector>

#include "Entity.hpp"
#include "Obstacle.hpp"
#include "ResourceIdentifiers.hpp"
#include "World.hpp"

class Lane : public Entity {
   public:
    // Type
    enum Type {
        Grass,
        LilyPadAbove,
        LilyPadBelow,
        LilyPadSingle,
        PavementAbove,
        PavementBelow,
        Railway,
        RoadAbove,
        RoadBelow,
        RoadMiddle,
        RoadSingle,
        TypeCount
    };

    // Direction of obstacles
    enum Direction {
        Left = -1,
        NoDirection = 0,
        Right = 1,
    };

    Lane(Type type, Direction direction, float speed);
    void setSpawnRate(int x);

   private:
    virtual void drawCurrent(sf::RenderTarget& target,
                             sf::RenderStates states) const override;
    virtual void updateCurrent(sf::Time dt, CommandQueue& commands) override;
    virtual unsigned int getCategory() const override;

    void generateObstacle(sf::Time dt);

    Type mType;
    Direction mDirection;
    float mSpeed;
    sf::Sprite mSprite;
    int spawnRate;
};