#include "Application.hpp"

#include "ChooseCharacterState.hpp"
#include "Constants.hpp"
#include "GameOverState.hpp"
#include "GameState.hpp"
#include "LevelUpState.hpp"
#include "MenuState.hpp"
#include "PauseState.hpp"
#include "SettingsState.hpp"
#include "LoadGameState.hpp"
#include "State.hpp"
#include "StateIdentifiers.hpp"
#include "TitleState.hpp"
#include "Utility.hpp"

const sf::Time Application::TimePerFrame = sf::seconds(1.f / 60.f);  // 60 fps

Application::Application()
    : mWindow(sf::VideoMode(Constants::SCREEN_WIDTH, Constants::SCREEN_HEIGHT),
              "Crossing Road", sf::Style::Close),
      mTextures(),
      mFonts(),
      mMusic(),
      mSounds(),
      mPlayer(),
      mStateStack(State::Context(mWindow, mTextures, mFonts, mPlayer, mMusic,
                                 mSounds)) {
    mWindow.setKeyRepeatEnabled(true);

    registerStates();
    mStateStack.pushState(States::Title);

    SettingsSingleton::getInstance().setSoundPlayer(&mSounds);
    SettingsSingleton::getInstance().setMusicPlayer(&mMusic);
}

void Application::run() {
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;

    while (mWindow.isOpen()) {
        sf::Time dt = clock.restart();
        timeSinceLastUpdate += dt;
        while (timeSinceLastUpdate > TimePerFrame) {
            timeSinceLastUpdate -= TimePerFrame;
            processInput();
            update(TimePerFrame);
            if (mStateStack.isEmpty()) mWindow.close();
        }
        render();
    }
}

void Application::processInput() {
    sf::Event event;
    while (mWindow.pollEvent(event)) {
        mStateStack.handleEvent(event);
        if (event.type == sf::Event::Closed) mWindow.close();
    }
}

void Application::update(sf::Time dt) {
    mStateStack.update(dt);
}

void Application::render() {
    mWindow.clear();
    mStateStack.draw();
    mWindow.display();
}

void Application::registerStates() {
    mStateStack.registerState<TitleState>(States::Title);
    mStateStack.registerState<MenuState>(States::Menu);
    mStateStack.registerState<GameState>(States::Game);
    mStateStack.registerState<PauseState>(States::Pause);
    mStateStack.registerState<SettingsState>(States::Settings);
    mStateStack.registerState<GameOverState>(States::GameOver);
    mStateStack.registerState<ChooseCharacterState>(States::ChooseCharacter);
    mStateStack.registerState<LevelUpState>(States::LevelUp);
    mStateStack.registerState<LoadGameState>(States::LoadGame);
}
