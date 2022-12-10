#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "Entity.hpp"
#include "ResourceIdentifiers.hpp"

class Obstacle : public Entity {
   public:
    enum Type {
        BlueBusLeft,
        BlueBusRight,
        BlueCarLeft,
        BlueCarRight,
        GrayCarLeft,
        GrayCarRight,
        NewVanLeft,
        NewVanRight,
        OldVanLeft,
        OldVanRight,
        OrangeBusLeft,
        OrangeBusRight,
        PoliceCarLeft,
        PoliceCarRight,
        RedCarLeft,
        RedCarRight,
        RedStripedCarLeft,
        RedStripedCarRight,
        RedTruckLeft,
        RedTruckRight,
        SchoolBusLeft,
        SchoolBusRight,
        WhiteTruckLeft,
        WhiteTruckRight,
        YellowCabLeft,
        YellowCabRight,
        YellowCarLeft,
        YellowCarRight,
    };

    Obstacle(Type type);
    virtual sf::FloatRect getBoundingRect() const;

   private:
    virtual void drawCurrent(sf::RenderTarget& target,
                             sf::RenderStates states) const;

    virtual unsigned int getCategory() const;

    Type mType;
    sf::Sprite mSprite;
};
