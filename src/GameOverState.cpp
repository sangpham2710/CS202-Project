#include "GameOverState.hpp"

#include "MusicPlayer.hpp"
#include "SettingsSingleton.hpp"
#include "Utility.hpp"

GameOverState::GameOverState(StateStack& stack, Context context)
    : State(stack, context) {
    sf::RenderWindow& window = *getContext().window;
    gui->loadWidgetsFromFile("./assets/gui/game-over-state.txt");

#define gameOverLabel gui->get<tgui::Label>("gameOverLabel")
    alignCenter(gameOverLabel, window);

    context.music->play(Music::GameOverTheme);
#undef gameOverLabel
}
void GameOverState::draw() {
    gui->draw();
}

bool GameOverState::update(sf::Time dt) {
    mElapsedTime += dt;
    if (mElapsedTime > sf::seconds(2)) {
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