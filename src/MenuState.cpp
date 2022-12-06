#include "MenuState.hpp"

#include "Utility.hpp"

MenuState::MenuState(StateStack& stack, Context context)
    : State(stack, context) {
    sf::RenderWindow& window = *getContext().window;
    gui->loadWidgetsFromFile("./assets/gui/menu-state.txt");

    auto menuLabel = gui->get<tgui::Label>("menuLabel");
    auto playBtn = gui->get<tgui::Button>("playButton");
    auto settingsBtn = gui->get<tgui::Button>("settingsButton");
    auto exitBtn = gui->get<tgui::Button>("exitButton");

    alignCenter(menuLabel, window);

    playBtn->onPress([&] {
        requestStackPop();
        requestStackPush(States::Game);
    });
    alignCenter(playBtn, window);

    settingsBtn->onPress([&] { requestStackPush(States::Settings); });
    alignCenter(settingsBtn, window);

    exitBtn->onPress([&] { requestStackPop(); });
    alignCenter(exitBtn, window);
}

void MenuState::draw() {
    gui->draw();
}

bool MenuState::update(sf::Time dt) {
    return true;
}

bool MenuState::handleEvent(const sf::Event& event) {
    gui->handleEvent(event);
    return false;
}