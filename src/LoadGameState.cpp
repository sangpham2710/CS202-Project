#include "LoadGameState.hpp"

#include <iostream>

#include "Constants.hpp"
#include "MusicPlayer.hpp"
#include "SettingsSingleton.hpp"
#include "SoundNode.hpp"
#include "Utility.hpp"

LoadGameState::LoadGameState(StateStack& stack, Context context)
    : State(stack, context) {
    sf::RenderWindow& window = *getContext().window;
    gui->loadWidgetsFromFile("./assets/gui/load-game-state.txt");

#define loadGameLabel gui->get<tgui::Label>("loadGameLabel")
#define inputLabel gui->get<tgui::Label>("inputLabel")
#define inputBox gui->get<tgui::EditBox>("inputBox")
#define statusLabel gui->get<tgui::Label>("statusLabel")
#define loadGroup gui->get<tgui::Group>("loadGroup")
#define loadButton gui->get<tgui::Button>("loadButton")
#define chooseButton gui->get<tgui::Button>("chooseButton")
#define backButton gui->get<tgui::Button>("backButton")

    auto playButtonHoverSound = [&] {
        getContext().sounds->play(SoundEffect::ButtonHover);
    };

    loadButton->onMouseEnter(playButtonHoverSound);
    backButton->onMouseEnter(playButtonHoverSound);

    alignCenter(loadGameLabel, window);
    alignCenter(inputLabel, window);
    alignCenter(inputBox, window);
    alignCenter(loadGroup, window);
    alignCenter(backButton, window);

    statusLabel->setInheritedOpacity(0.0);
    loadButton->onPress([&] {
        getContext().sounds->play(SoundEffect::ButtonClick);
        requestStackPop();
        requestStackPop();
        SettingsSingleton::getInstance().setIsLevelLoaded(true);
        SettingsSingleton::getInstance().setLoadingLevelFilename(
            inputBox->getText().toStdString());
        requestStackPush(States::Game);
        requestStackPush(States::LevelUp);
    });

    chooseButton->onPress([&] {
        getContext().sounds->play(SoundEffect::ButtonClick);
        auto dialog = tgui::FileDialog::create();
        dialog->setWidgetName("fileDialog");
        gui->add(dialog);

#define fileDialog gui->get<tgui::FileDialog>("fileDialog")

        fileDialog->setFileMustExist(true);
        fileDialog->setFocused(true);
        // gui is a unique_ptr to a tgui::Gui object
        fileDialog->onFileSelect([&]() {
            inputBox->setText(fileDialog->getSelectedPaths()[0].asString());
            fileDialog->close();
        });
        fileDialog->onCancel([&] { fileDialog->close(); });

#undef fileDialog
    });

    backButton->onPress([&] {
        getContext().sounds->play(SoundEffect::ButtonClick);
        requestStackPop();
    });

#undef loadGameLabel
#undef inputLabel
#undef inputBox
#undef statusLabel
#undef loadButton
#undef chooseButton
#undef backButton
}
void LoadGameState::draw() {
    gui->draw();
}

bool LoadGameState::update(sf::Time dt) {
    return true;
}

bool LoadGameState::handleEvent(const sf::Event& event) {
    gui->handleEvent(event);
    return false;
}