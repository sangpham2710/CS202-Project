#include "TitleState.hpp"

#include "Utility.hpp"

TitleState::TitleState(StateStack& stack, Context context)
    : State(stack, context), mText() {
}

void TitleState::draw() {
    sf::RenderWindow& window = *getContext().window;
    window.draw(mBackgroundSprite);
}

bool TitleState::update(sf::Time dt) {
    return false;
}

bool TitleState::handleEvent(const sf::Event& event) {
    // If any key is pressed, trigger the next screen
    if (event.type == sf::Event::KeyPressed) {
        requestStackPop();
        requestStackPush(States::Game);
    }

    return true;
}