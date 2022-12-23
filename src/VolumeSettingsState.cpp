#include "VolumeSettingsState.hpp"
#include "SettingsSingleton.hpp"
#include "Utility.hpp"

#include <iostream>
VolumeSettingsState::VolumeSettingsState(StateStack& stack, Context context)
    : State(stack, context) {
    sf::RenderWindow& window = *getContext().window;
    gui->loadWidgetsFromFile("./assets/gui/change-volume-state.txt");

    auto volumeLabel = gui->get<tgui::Label>("volumeLabel");
    auto soundLabel = gui->get<tgui::Label>("soundLabel");
    auto musicLabel = gui->get<tgui::Label>("musicLabel");
    auto soundSlider = gui->get<tgui::Slider>("soundSlider");
    auto musicSlider = gui->get<tgui::Slider>("musicSlider");
    auto backButton = gui->get<tgui::Button>("backButton");
    
    alignCenter(volumeLabel, window);
    alignCenter(soundLabel, window);
    alignCenter(musicLabel, window);
    alignCenter(soundSlider, window);
    alignCenter(musicSlider, window);

    soundLabel->setPosition(soundLabel->getPosition().x - 100, soundLabel->getPosition().y);
    musicLabel->setPosition(musicLabel->getPosition().x - 100, musicLabel->getPosition().y);

    soundSlider->setPosition(soundSlider->getPosition().x + 100, soundSlider->getPosition().y);
    musicSlider->setPosition(musicSlider->getPosition().x + 100, musicSlider->getPosition().y);


    soundSlider->setMaximum(25);
    soundSlider->setMinimum(0);
    soundSlider->setValue(SettingsSingleton::getInstance().getSoundVolume());

    musicSlider->setMaximum(25);
    musicSlider->setMinimum(0);
    musicSlider->setValue(SettingsSingleton::getInstance().getMusicVolume());

    backButton->onPress([&] { requestStackPop(); });
}

void VolumeSettingsState::draw() {
    gui->draw();
}

bool VolumeSettingsState::update(sf::Time dt) {
    auto soundSlider = gui->get<tgui::Slider>("soundSlider");
    auto musicSlider = gui->get<tgui::Slider>("musicSlider");

    SettingsSingleton::getInstance().setSoundVolume(soundSlider->getValue());
    SettingsSingleton::getInstance().setMusicVolume(musicSlider->getValue());
    return true;
}

bool VolumeSettingsState::handleEvent(const sf::Event& event) {
    gui->handleEvent(event);
    return false;
}