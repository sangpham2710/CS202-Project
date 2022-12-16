#include "SettingsState.hpp"

#include "Utility.hpp"

SettingsState::SettingsState(StateStack& stack, Context context)
    : State(stack, context) {
    sf::RenderWindow& window = *getContext().window;
    gui->loadWidgetsFromFile("./assets/gui/settings-state.txt");

    auto settingsLabel = gui->get<tgui::Label>("settingsLabel");
    auto characterButton = gui->get<tgui::Button>("characterButton");
    auto backButton = gui->get<tgui::Button>("backButton");

    alignCenter(settingsLabel, window);
    alignCenter(characterButton, window);
    alignCenter(backButton, window);

    characterButton->onPress([&] {
        requestStackPush(States::ChooseCharacter);
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