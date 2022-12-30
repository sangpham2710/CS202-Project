#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

#include "State.hpp"

class LevelUpState : public State {
   public:
    LevelUpState(StateStack& stack, Context context);

    virtual void draw() override;
    virtual bool update(sf::Time dt) override;
    virtual bool handleEvent(const sf::Event& event) override;

   private:
    sf::Time mElapsedTime;
};
