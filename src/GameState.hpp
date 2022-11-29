#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

#include "Player.hpp"
#include "State.hpp"
#include "World.hpp"


class GameState : public State {
   public:
    GameState(StateStack& stack, Context context);

    virtual void draw();
    virtual bool update(sf::Time dt);
    virtual bool handleEvent(const sf::Event& event);

   private:
    World mWorld;
    Player& mPlayer;
};