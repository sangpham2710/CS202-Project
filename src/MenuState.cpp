#include "MenuState.hpp"

#include "Utility.hpp"

MenuState::MenuState(StateStack& stack, Context context)
    : State(stack, context) {
    sf::RenderWindow& window = *getContext().window;
    gui->loadWidgetsFromFile("./assets/gui/menu-state.txt");

    gui->setFont("./assets/Sansation.ttf");

    auto menulabel = gui->get<tgui::Label>("menuLabel");
    auto playBtn = gui->get<tgui::Button>("playButton");
    auto settingsBtn = gui->get<tgui::Button>("settingsButton");
    auto exitBtn = gui->get<tgui::Button>("exitButton");

    alignCenter(menulabel, window);

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
    sf::RenderWindow& window = *getContext().window;

    sf::RectangleShape rectangle(sf::Vector2f(1024, 768));
    rectangle.setFillColor(sf::Color::Green);
    window.draw(rectangle);

    gui->draw();
}

bool MenuState::update(sf::Time dt) {
    return true;
}

bool MenuState::handleEvent(const sf::Event& event) {
    gui->handleEvent(event);
    return true;
}