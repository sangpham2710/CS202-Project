#include "PauseState.hpp"

#include "Constants.hpp"
#include "SettingsSingleton.hpp"
#include "SoundNode.hpp"
#include "Utility.hpp"

PauseState::PauseState(StateStack& stack, Context context)
    : State(stack, context) {
    sf::RenderWindow& window = *getContext().window;
    gui->loadWidgetsFromFile("./assets/gui/pause-state.txt");

#define pauseLabel gui->get<tgui::Label>("pauseLabel")
#define continueButton gui->get<tgui::Button>("continueButton")
#define saveButton gui->get<tgui::Button>("saveButton")
#define settingsButton gui->get<tgui::Button>("settingsButton")
#define backToMenuButton gui->get<tgui::Button>("backToMenuButton")

    alignCenter(pauseLabel, window);
    alignCenter(continueButton, window);
    alignCenter(saveButton, window);
    alignCenter(settingsButton, window);
    alignCenter(backToMenuButton, window);

    auto playButtonHoverSound = [&] {
        getContext().sounds->play(SoundEffect::ButtonHover);
    };

    continueButton->onMouseEnter(playButtonHoverSound);
    saveButton->onMouseEnter(playButtonHoverSound);
    settingsButton->onMouseEnter(playButtonHoverSound);
    backToMenuButton->onMouseEnter(playButtonHoverSound);


    continueButton->onPress([&] {
        getContext().sounds->play(SoundEffect::ButtonClick);
        requestStackPop();
    });
    saveButton->onPress([&] {
        getContext().sounds->play(SoundEffect::ButtonClick);
        SettingsSingleton::getInstance().setIsLevelSaving(true);
        requestStackPop();
    });
    settingsButton->onPress([&] {
        getContext().sounds->play(SoundEffect::ButtonClick);
        requestStackPush(States::Settings);
    });

    backToMenuButton->onPress([&] {
        getContext().sounds->play(SoundEffect::ButtonClick);
        requestStateClear();
        requestStackPush(States::Menu);
    });

#undef pauseLabel
#undef continueButton
#undef saveButton
#undef settingsButton
#undef backToMenuButton
}

void PauseState::draw() {
    gui->draw();
}

bool PauseState::update(sf::Time dt) {
    return false;
}

bool PauseState::handleEvent(const sf::Event& event) {
    gui->handleEvent(event);
    return false;
}