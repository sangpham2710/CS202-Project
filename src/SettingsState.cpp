#include "SettingsState.hpp"
#include "SettingsSingleton.hpp"

#include "Utility.hpp"

SettingsState::SettingsState(StateStack& stack, Context context)
    : State(stack, context) {
    sf::RenderWindow& window = *getContext().window;
    gui->loadWidgetsFromFile("./assets/gui/settings-state.txt");

    auto settingsLabel = gui->get<tgui::Label>("settingsLabel");
    auto soundLabel = gui->get<tgui::Label>("soundLabel");
    auto musicLabel = gui->get<tgui::Label>("musicLabel");
    auto soundSlider = gui->get<tgui::Slider>("soundSlider");
    auto musicSlider = gui->get<tgui::Slider>("musicSlider");
    auto characterButton = gui->get<tgui::Button>("characterButton");
    auto backButton = gui->get<tgui::Button>("backButton");

    alignCenter(settingsLabel, window);
    alignCenter(soundLabel, window);
    alignCenter(musicLabel, window);
    alignCenter(soundSlider, window);
    alignCenter(musicSlider, window);
    alignCenter(characterButton, window);
    alignCenter(backButton, window);

    soundLabel->setPosition(soundLabel->getPosition().x - 400, soundLabel->getPosition().y);
    soundSlider->setPosition(soundSlider->getPosition().x - 200, soundSlider->getPosition().y);
    musicLabel->setPosition(musicLabel->getPosition().x + 100, musicLabel->getPosition().y);
    musicSlider->setPosition(musicSlider->getPosition().x + 300, musicSlider->getPosition().y);

    characterButton->onPress([&] {
        requestStackPush(States::ChooseCharacter);
    });

    backButton->onPress([&] { requestStackPop(); });

    soundSlider->setMaximum(25);
    soundSlider->setMinimum(0);
    soundSlider->setValue(SettingsSingleton::getInstance().getSoundVolume());

    musicSlider->setMaximum(25);
    musicSlider->setMinimum(0);
    musicSlider->setValue(SettingsSingleton::getInstance().getMusicVolume());

    soundSlider->onValueChange([&] {
        SettingsSingleton::getInstance().setSoundVolume(soundSlider->getValue());
    });
    musicSlider->onValueChange([&] {
        SettingsSingleton::getInstance().setMusicVolume(musicSlider->getValue());
    });
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