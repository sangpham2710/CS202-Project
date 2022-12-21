#include "levelUpState.hpp"

#include "SettingsSingleton.hpp"
#include "Utility.hpp"

levelUpState::levelUpState(StateStack& stack, Context context)
    : State(stack, context) {
    sf::RenderWindow& window = *getContext().window;
    gui->loadWidgetsFromFile("./assets/gui/level-up-state.txt");

    auto levelLabel = gui->get<tgui::Label>("levelLabel");
    std::string currentLevel = std::to_string(
        SettingsSingleton::getInstance().getCurrentLevelNumber());
    levelLabel->setText("LEVEL " + currentLevel);

    alignCenter(levelLabel, window);
}
void levelUpState::draw() {
    gui->draw();
}

bool levelUpState::update(sf::Time dt) {
    mElapsedTime += dt;
    if (mElapsedTime > sf::seconds(1.5)) {
        requestStackPop();
    }
    return false;
}

bool levelUpState::handleEvent(const sf::Event& event) {
    gui->handleEvent(event);
    return false;
}