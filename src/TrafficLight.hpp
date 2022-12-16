#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "Entity.hpp"
#include "ResourceIdentifiers.hpp"

class TrafficLight : public Entity {
   public:
    enum class State { Green, Yellow, Red };

    TrafficLight();
    State getState();  // 0 red 1 yellow 2 green
   private:
    virtual void drawCurrent(sf::RenderTarget& target,
                             sf::RenderStates states) const override;
    virtual void updateCurrent(sf::Time dt, CommandQueue& commands) override;

    State mCurrentState;
    sf::Sprite mSprite;
    sf::Time elapsedTime;
};
