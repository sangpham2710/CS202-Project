#include "TitleState.hpp"

#include <iostream>

#include "Utility.hpp"

TitleState::TitleState(StateStack& stack, Context context)
    : State(stack, context),isIncreasingOpacity(false) {
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
    
    double currentOpacity = titlelabel->getInheritedOpacity();
    
    if (isIncreasingOpacity) {
        currentOpacity += dt.asSeconds();
        titlelabel->setInheritedOpacity(std::min(currentOpacity, 1.0));

        if (currentOpacity >= 1) {
            currentOpacity = 1;
            isIncreasingOpacity = false;
        }
        else {
            isIncreasingOpacity = true;
        }
    }
    else {
        currentOpacity -= dt.asSeconds();
        titlelabel->setInheritedOpacity(std::max(currentOpacity, 0.0));

        if (currentOpacity <= 0) {
            currentOpacity = 0;
            isIncreasingOpacity = true;
        }
        else {
            isIncreasingOpacity = false;
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