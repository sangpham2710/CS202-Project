#include "SettingsState.hpp"

#include <iostream>

#include "Utility.hpp"

SettingsState::SettingsState(StateStack& stack, Context context)
    : State(stack, context) {
    auto backButton = tgui::Button::create();
    backButton->setTextSize(30);
    backButton->setPosition(100, 500);
    backButton->setSize(200, 100);
    backButton->setText("Back");
    backButton->onPress([&]() { requestStackPop(); });
    gui->add(backButton);
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