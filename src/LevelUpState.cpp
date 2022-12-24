#include "levelUpState.hpp"

#include "MusicPlayer.hpp"
#include "SettingsSingleton.hpp"
#include "Utility.hpp"

LevelUpState::LevelUpState(StateStack& stack, Context context)
    : State(stack, context) {
    sf::RenderWindow& window = *getContext().window;
    gui->loadWidgetsFromFile("./assets/gui/level-up-state.txt");
    auto levelLabel = gui->get<tgui::Label>("levelLabel");
    std::string currentLevel = std::to_string(
        SettingsSingleton::getInstance().getCurrentLevelNumber());
    levelLabel->setText("LEVEL " + currentLevel);

    alignCenter(levelLabel, window);

    context.music->play(Music::LevelUpTheme);
}
void LevelUpState::draw() {
    gui->draw();
}

bool LevelUpState::update(sf::Time dt) {
    mElapsedTime += dt;
    if (mElapsedTime > sf::seconds(1.5)) {
        requestStackPop();
        getContext().music->play(Music::MissionTheme);
    }
    return false;
}

bool LevelUpState::handleEvent(const sf::Event& event) {
    gui->handleEvent(event);
    return false;
}