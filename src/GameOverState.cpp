#include "GameOverState.hpp"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>

#include "ResourceHolder.hpp"
#include "ResourceIdentifiers.hpp"
#include "Utility.hpp"

GameOverState::GameOverState(StateStack& stack, Context context)
    : State(stack, context) {
    sf::RenderWindow& window = *getContext().window;
    gui->loadWidgetsFromFile("./assets/gui/gameOver-state.txt");

    auto titlelabel = gui->get<tgui::Label>("gameOverLabel");
    auto replayBtn = gui->get<tgui::Button>("replayButton");
    auto menuBtn = gui->get<tgui::Button>("backToMenuButton");

    alignCenter(titlelabel, window);
    alignCenter(replayBtn, window);
    alignCenter(menuBtn, window);

    replayBtn->onPress([&] {
        requestStateClear();
        requestStackPush(States::Game);
    });
    menuBtn->onPress([&] {
        requestStateClear();
        requestStackPush(States::Menu);
    });
}

void GameOverState::draw() {
    gui->draw();
}

bool GameOverState::update(sf::Time) {
    return false;
}

bool GameOverState::handleEvent(const sf::Event& event) {
    gui->handleEvent(event);
    return false;
}