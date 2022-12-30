#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <array>

#include "Command.hpp"
#include "CommandQueue.hpp"
#include "Player.hpp"
#include "SceneNode.hpp"
#include "State.hpp"

class SettingsState : public State {
   public:
    SettingsState(StateStack& stack, Context context);

    virtual void draw() override;
    virtual bool update(sf::Time dt) override;
    virtual bool handleEvent(const sf::Event& event) override;

   private:
    SceneNode mSceneGraph;
    CommandQueue mCommandQueue;
};
