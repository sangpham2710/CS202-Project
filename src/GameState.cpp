#include "GameState.hpp"

#include "MusicPlayer.hpp"
#include "SettingsSingleton.hpp"

GameState::GameState(StateStack& stack, Context context)
    : State(stack, context),
      mWorld(*context.window, *context.fonts, *context.sounds),
      mPlayer(*context.player) {
    context.music->play(Music::MissionTheme);
}

void GameState::draw() {
    mWorld.draw();
}

bool GameState::update(sf::Time dt) {
    mWorld.update(dt);

    if (!mWorld.hasAlivePlayer()) {
        requestStackPush(States::GameOver);
    } else if (mWorld.hasPlayerReachedEnd()) {
        SettingsSingleton::getInstance().setCurrentLevelNumber(
            SettingsSingleton::getInstance().getCurrentLevelNumber() + 1);
        requestStackPop();
        requestStackPush(States::Game);
        requestStackPush(States::LevelUp);
    }

    CommandQueue& commands = mWorld.getCommandQueue();
    mPlayer.handleRealtimeInput(commands);

    return true;
}

bool GameState::handleEvent(const sf::Event& event) {
    // Game input handling
    CommandQueue& commands = mWorld.getCommandQueue();
    mPlayer.handleEvent(event, commands);

    // Escape pressed, trigger the pause screen
    if (event.type == sf::Event::KeyPressed &&
        event.key.code == sf::Keyboard::Escape) {
        requestStackPush(States::Pause);
    }

    return true;
}