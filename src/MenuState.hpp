#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

#include "Command.hpp"
#include "CommandQueue.hpp"
#include "SceneNode.hpp"
#include "State.hpp"

class MenuState : public State {
   public:
    MenuState(StateStack& stack, Context context);

    virtual void draw() override;
    virtual bool update(sf::Time dt) override;
    virtual bool handleEvent(const sf::Event& event) override;
};
