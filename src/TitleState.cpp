#include "TitleState.hpp"

#include <iostream>

#include "Utility.hpp"

TitleState::TitleState(StateStack& stack, Context context)
    : State(stack, context), isIncreasing(false) {
    sf::RenderWindow& window = *getContext().window;
    gui->loadWidgetsFromFile("./assets/gui/title-state.txt");

    auto titlelabel = gui->get<tgui::Label>("titleLabel");
    alignCenter(titlelabel, window);
}

void TitleState::draw() {
    sf::RenderWindow& window = *getContext().window;

    sf::RectangleShape rectangle(sf::Vector2f(1024, 768));
    rectangle.setFillColor(sf::Color::White);
    window.draw(rectangle);

    gui->draw();
}

bool TitleState::update(sf::Time dt) {
    auto titlelabel = gui->get<tgui::Label>("titleLabel");
    float currentOpacity = titlelabel->getInheritedOpacity();
    if (isIncreasing) {
        currentOpacity += (float)dt.asSeconds();
        titlelabel->setInheritedOpacity(currentOpacity);
        if (currentOpacity > 1) {
            isIncreasing = false;
            titlelabel->setInheritedOpacity(1.0);
        }
    }
    else {
        currentOpacity -= (float)dt.asSeconds();
        titlelabel->setInheritedOpacity(currentOpacity);
        if (currentOpacity < 0) {
            isIncreasing = true;
            titlelabel->setInheritedOpacity(0.0);
        }
    }
    return true;
}

bool TitleState::handleEvent(const sf::Event& event) {
    gui->handleEvent(event);
    // If mouse button pressed, trigger the next screen
    if (event.type == sf::Event::MouseButtonPressed) {
        requestStackPop();
        requestStackPush(States::Menu);
    }
    return false;
}