#include "SettingsState.hpp"

#include "Utility.hpp"

SettingsState::SettingsState(StateStack& stack, Context context)
    : State(stack, context) {
    sf::RenderWindow& window = *getContext().window;
    gui->loadWidgetsFromFile("./assets/gui/settings-state.txt");

    auto settingsLabel = gui->get<tgui::Label>("settingsLabel");
    auto characterButton = gui->get<tgui::Button>("characterButton");
    auto volumeButton = gui->get<tgui::Button>("volumeButton");
    auto backButton = gui->get<tgui::Button>("backButton");

    alignCenter(settingsLabel, window);
    alignCenter(characterButton, window);
    alignCenter(volumeButton, window);
    alignCenter(backButton, window);

    characterButton->onPress([&] {
        requestStackPush(States::ChooseCharacter);
    });
    volumeButton->onPress([&] {
        requestStackPush(States::VolumeSettings);
    });
    backButton->onPress([&] { requestStackPop(); });
}

void SettingsState::draw() {
    gui->draw();
}

bool SettingsState::update(sf::Time dt) {
    return true;
}

bool SettingsState::handleEvent(const sf::Event& event) {
    gui->handleEvent(event);
    return false;
}