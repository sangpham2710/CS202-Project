#include "TitleState.hpp"

#include <iostream>

#include "Utility.hpp"

TitleState::TitleState(StateStack& stack, Context context)
    : State(stack, context) {
    gui->loadWidgetsFromFile("./assets/gui/title-state.txt");
}

void TitleState::draw() {
    sf::RenderWindow& window = *getContext().window;

    sf::RectangleShape rectangle(sf::Vector2f(1024, 768));
    rectangle.setFillColor(sf::Color::White);
    window.draw(rectangle);

    sf::Texture texture;
    if (!texture.loadFromFile("./assets/textures/vehicles/blue-bus-left.png")) {
    }
    sf::Sprite sprite;
    sprite.setTexture(texture);
    // auto tmp = 64.0 / texture.getSize().x;
    // sprite.setScale(tmp, tmp);
    sprite.setPosition(100, 100);
    centerOrigin(sprite);
    sprite.rotate(90);

    window.draw(sprite);
    gui->draw();
}

bool TitleState::update(sf::Time dt) {
    return true;
}

bool TitleState::handleEvent(const sf::Event& event) {
    gui->handleEvent(event);
    // If mouse button pressed, trigger the next screen
    if (event.type == sf::Event::MouseButtonPressed) {
        requestStackPop();
        requestStackPush(States::Menu);
    }
    return true;
}