#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <array>

#include "Player.hpp"
#include "State.hpp"
#include "VolumeSettingsState.hpp"

class VolumeSettingsState : public State {
public:
    VolumeSettingsState(StateStack& stack, Context context);

    virtual void draw() override;
    virtual bool update(sf::Time dt) override;
    virtual bool handleEvent(const sf::Event& event) override;
};