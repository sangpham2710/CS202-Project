#include "MenuState.hpp"

#include "Constants.hpp"
#include "MusicPlayer.hpp"
#include "SettingsSingleton.hpp"
#include "SoundNode.hpp"
#include "Utility.hpp"

MenuState::MenuState(StateStack& stack, Context context)
    : State(stack, context) {
    sf::RenderWindow& window = *getContext().window;
    gui->loadWidgetsFromFile("./assets/gui/menu-state.txt");

#define menuLabel gui->get<tgui::Label>("menuLabel")
#define playButton gui->get<tgui::Button>("playButton")
#define loadButton gui->get<tgui::Button>("loadButton")
#define settingsButton gui->get<tgui::Button>("settingsButton")
#define exitButton gui->get<tgui::Button>("exitButton")
#define menuPanel gui->get<tgui::Panel>("menuPanel")

    auto playButtonHoverSound = [&] {
        getContext().sounds->play(SoundEffect::ButtonHover);
    };

    playButton->onMouseEnter(playButtonHoverSound);
    loadButton->onMouseEnter(playButtonHoverSound);
    settingsButton->onMouseEnter(playButtonHoverSound);
    exitButton->onMouseEnter(playButtonHoverSound);

    alignCenter(menuLabel, window);

    playButton->onPress([&] {
        getContext().sounds->play(SoundEffect::ButtonClick);
        requestStackPop();
        SettingsSingleton::getInstance().setIsLevelLoaded(false);
        SettingsSingleton::getInstance().setCurrentLevelNumber(1);
        requestStackPush(States::Game);
        requestStackPush(States::LevelUp);
    });
    alignCenter(playButton, window);

    loadButton->onPress([&] {
        getContext().sounds->play(SoundEffect::ButtonClick);
        requestStackPush(States::LoadGame);
    });

    alignCenter(loadButton, window);

    settingsButton->onPress([&] {
        getContext().sounds->play(SoundEffect::ButtonClick);
        requestStackPush(States::Settings);
    });

    alignCenter(settingsButton, window);

    exitButton->onPress([&] {
        getContext().sounds->play(SoundEffect::ButtonClick);
        requestStackPop();
    });
    alignCenter(exitButton, window);

    context.music->play(Music::MenuTheme);

#undef menuLabel
#undef playButton
#undef loadButton
#undef settingsButton
#undef exitButton
}

void MenuState::draw() {
    gui->draw();
}

bool MenuState::update(sf::Time dt) {
    return true;
}

bool MenuState::handleEvent(const sf::Event& event) {
    gui->handleEvent(event);
    return false;
}