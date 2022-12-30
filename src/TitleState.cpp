#include "TitleState.hpp"

#include "Utility.hpp"

TitleState::TitleState(StateStack& stack, Context context)
    : State(stack, context), isIncreasing(false) {
    sf::RenderWindow& window = *getContext().window;
    gui->loadWidgetsFromFile("./assets/gui/title-state.txt");

#define titleLabel gui->get<tgui::Label>("titleLabel")
    alignCenter(titleLabel, window);
#undef titleLabel
}

void TitleState::draw() {
    sf::RenderWindow& window = *getContext().window;

    sf::RectangleShape rectangle(sf::Vector2f(1024, 768));
    rectangle.setFillColor(sf::Color::White);
    window.draw(rectangle);

    gui->draw();
}

bool TitleState::update(sf::Time dt) {
#define titleLabel gui->get<tgui::Label>("titleLabel")
    float currentOpacity = titleLabel->getInheritedOpacity();
    if (isIncreasing) {
        currentOpacity += (float)dt.asSeconds();
        titleLabel->setInheritedOpacity(currentOpacity);
        if (currentOpacity > 1) {
            isIncreasing = false;
            titleLabel->setInheritedOpacity(1.0);
        }
    } else {
        currentOpacity -= (float)dt.asSeconds();
        titleLabel->setInheritedOpacity(currentOpacity);
        if (currentOpacity < 0) {
            isIncreasing = true;
            titleLabel->setInheritedOpacity(0.0);
        }
    }
    return true;
#undef titleLabel
}

bool TitleState::handleEvent(const sf::Event& event) {
    gui->handleEvent(event);
    // If mouse button pressed, trigger the next screen
    if (event.type == sf::Event::MouseButtonPressed) {
        requestStackPop();
        requestStackPush(States::Menu);
    }
    // If any key is pressed, trigger the next screen
    if (event.type == sf::Event::KeyPressed) {
        requestStackPop();
        requestStackPush(States::Menu);
    }
    return false;
}