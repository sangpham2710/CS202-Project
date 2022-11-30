#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

#include "State.hpp"

class MenuState : public State {
   public:
    MenuState(StateStack& stack, Context context);

    virtual void draw();
    virtual bool update(sf::Time dt);
    virtual bool handleEvent(const sf::Event& event);

   private:
    tgui::Button::Ptr mGameButton;
    tgui::Button::Ptr mSettingsButton;
    tgui::Button::Ptr mExitButton;
};
