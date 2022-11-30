#include "TitleState.hpp"

#include "Utility.hpp"

TitleState::TitleState(StateStack& stack, Context context)
    : State(stack, context) {
    mPlayButton = tgui::Button::create();
    mPlayButton->setTextSize(30);
    mPlayButton->setText("Play");
    mPlayButton->setPosition("50%", "50%");
    mPlayButton->setSize(200, 100);
    mPlayButton->onPress([&]() {
        requestStackPop();
        requestStackPush(States::Menu);
    });
    gui->add(mPlayButton);
}

void TitleState::draw() {
    sf::RenderWindow& window = *getContext().window;

    sf::RectangleShape rectangle(sf::Vector2f(1024, 768));
    rectangle.setFillColor(sf::Color::White);
    window.draw(rectangle);

    gui->draw();
}

bool TitleState::update(sf::Time dt) {
    return true;
}

bool TitleState::handleEvent(const sf::Event& event) {
    gui->handleEvent(event);
    // If any key is pressed, trigger the next screen
    if (event.type == sf::Event::KeyPressed) {
        requestStackPop();
        requestStackPush(States::Menu);
    }
    return true;
}