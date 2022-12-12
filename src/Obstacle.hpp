#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "Entity.hpp"
#include "ResourceIdentifiers.hpp"

class Obstacle : public Entity {
   public:
    enum class Type {
        BlueBus,
        BlueCar,
        GrayCar,
        NewVan,
        OldVan,
        OrangeBus,
        PoliceCar,
        RedCar,
        RedStripedCar,
        RedTruck,
        SchoolBus,
        WhiteTruck,
        YellowCab,
        YellowCar,
        TypeCount
    };
    enum class Direction { Left, Right };

    Obstacle(Type type, Direction direction);
    virtual sf::FloatRect getBoundingRect() const;

    static Obstacle::Type getRandomObstacleType();

    void setTextureWrecked();

   private:
    virtual void drawCurrent(sf::RenderTarget& target,
                             sf::RenderStates states) const;

    virtual unsigned int getCategory() const;

    Type mType;
    sf::Sprite mSprite;
};
