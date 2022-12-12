#include "GameOverState.hpp"

#include "Utility.hpp"

GameOverState::GameOverState(StateStack& stack, Context context)
    : State(stack, context) {
    sf::RenderWindow& window = *getContext().window;
    gui->loadWidgetsFromFile("./assets/gui/game-over-state.txt");

    auto gameOverLabel = gui->get<tgui::Label>("gameOverLabel");

    alignCenter(gameOverLabel, window);
}
void GameOverState::draw() {
    gui->draw();
}

bool GameOverState::update(sf::Time dt) {
    mElapsedTime += dt;
    if (mElapsedTime > sf::seconds(3)) {
        requestStateClear();
        requestStackPush(States::Menu);
    }
    return false;
}

bool GameOverState::handleEvent(const sf::Event& event) {
    // If any key is pressed, trigger the next screen
    if (event.type == sf::Event::KeyPressed &&
        event.key.code == sf::Keyboard::Escape) {
        requestStackPop();
        requestStackPush(States::Title);
    }
    return false;
}