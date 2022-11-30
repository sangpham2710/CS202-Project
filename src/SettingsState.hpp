#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <array>

#include "Player.hpp"
#include "State.hpp"


class SettingsState : public State {
   public:
    SettingsState(StateStack& stack, Context context);

    virtual void draw();
    virtual bool update(sf::Time dt);
    virtual bool handleEvent(const sf::Event& event);

   private:
    void updateLabels();
    void addButtonLabel(Player::Action action, float y, const std::string& text,
                        Context context);

   private:
    sf::Sprite mBackgroundSprite;
};
