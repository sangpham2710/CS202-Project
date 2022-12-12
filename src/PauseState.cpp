
#include "PauseState.hpp"

#include "Utility.hpp"

PauseState::PauseState(StateStack& stack, Context context)
    : State(stack, context) {
    sf::RenderWindow& window = *getContext().window;
    gui->loadWidgetsFromFile("./assets/gui/pause-state.txt");

    auto pauseLabel = gui->get<tgui::Label>("pauseLabel");
    auto continueBtn = gui->get<tgui::Button>("continueButton");
    auto settingsBtn = gui->get<tgui::Button>("settingsButton");
    auto backToMenuBtn = gui->get<tgui::Button>("backToMenuButton");

    alignCenter(pauseLabel, window);
    alignCenter(continueBtn, window);
    alignCenter(settingsBtn, window);
    alignCenter(backToMenuBtn, window);

    continueBtn->onPress([&] { requestStackPop(); });
    settingsBtn->onPress([&] { requestStackPush(States::Settings); });
    backToMenuBtn->onPress([&] {
        requestStateClear();
        requestStackPush(States::Menu);
    });
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