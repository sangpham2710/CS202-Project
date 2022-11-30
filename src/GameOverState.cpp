#include "GameOverState.hpp"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>

#include "ResourceHolder.hpp"
#include "ResourceIdentifiers.hpp"
#include "Utility.hpp"

GameOverState::GameOverState(StateStack& stack, Context context)
    : State(stack, context) {
}

void GameOverState::draw() {
    sf::RenderWindow& window = *getContext().window;
    sf::RectangleShape backgroundShape;
    backgroundShape.setFillColor(sf::Color(0, 0, 0, 150));
    backgroundShape.setSize(window.getView().getSize());
    window.draw(backgroundShape);
}

bool GameOverState::update(sf::Time) {
    return false;
}

bool GameOverState::handleEvent(const sf::Event& event) {
    // If any key is pressed, trigger the next screen
    if (event.type == sf::Event::KeyPressed) {
        requestStackPop();
        requestStackPush(States::Title);
    }
    return false;
}