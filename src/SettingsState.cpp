#include "SettingsState.hpp"

#include <iostream>

#include "Utility.hpp"

SettingsState::SettingsState(StateStack& stack, Context context)
    : State(stack, context) {

    gui->loadWidgetsFromFile("./assets/gui/settings-state.txt");

    gui->get<tgui::Button>("backButton")->onPress([&] {
        requestStackPop();
    });
}

void SettingsState::draw() {
    sf::RenderWindow& window = *getContext().window;

    sf::RectangleShape rectangle(sf::Vector2f(1024, 768));
    rectangle.setFillColor(sf::Color::Blue);
    window.draw(rectangle);

    gui->draw();
}

bool SettingsState::update(sf::Time dt) {
    return true;
}

bool SettingsState::handleEvent(const sf::Event& event) {
    gui->handleEvent(event);
    return true;
}