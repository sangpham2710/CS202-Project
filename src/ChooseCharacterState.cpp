#include "ChooseCharacterState.hpp"

#include "Utility.hpp"

#include <iostream>
ChooseCharacterState::ChooseCharacterState(StateStack& stack, Context context)
	:State(stack, context) {
    sf::RenderWindow& window = *getContext().window;
	gui->loadWidgetsFromFile("./assets/gui/choose-character-state.txt");

    auto characterLabel = gui->get<tgui::Label>("characterLabel");
    auto character1 = gui->get<tgui::Button>("character1");
    auto character2 = gui->get<tgui::Button>("character2");
    auto character3 = gui->get<tgui::Button>("character3");
    auto character4 = gui->get<tgui::Button>("character4");
    auto character5 = gui->get<tgui::Button>("character5");
    auto backButton = gui->get<tgui::Button>("backButton");

    alignCenter(characterLabel, window);
    alignCenter(backButton, window);
    alignCenter(character2, window);

    character2->setPosition(character2->getPosition().x - 20, character2->getPosition().y);
    character1->setPosition(character2->getPosition().x - 250, character2->getPosition().y);
    character3->setPosition(character2->getPosition().x + 250, character2->getPosition().y);

    alignCenter(character4, window);
    alignCenter(character5, window);

    character4->setPosition(character4->getPosition().x - 150, character4->getPosition().y);
    character5->setPosition(character5->getPosition().x + 110, character5->getPosition().y);

    backButton->onPress([&] { requestStackPop(); });

    character1->onPress([&] { 
        requestStackPop();
        SettingsSingleton::getInstance().setCharacterType(0);
        requestStackPush(States::ChooseCharacter);
    });
    character2->onPress([&] {
        requestStackPop();
        SettingsSingleton::getInstance().setCharacterType(1);
        requestStackPush(States::ChooseCharacter);
    });
    character3->onPress([&] {
        requestStackPop();
        SettingsSingleton::getInstance().setCharacterType(2);
        requestStackPush(States::ChooseCharacter);
    });
    character4->onPress([&] {
        requestStackPop();
        SettingsSingleton::getInstance().setCharacterType(3);
        requestStackPush(States::ChooseCharacter);
    });
    character5->onPress([&] {
        requestStackPop();
        SettingsSingleton::getInstance().setCharacterType(4);
        requestStackPush(States::ChooseCharacter);
    });
    
    int current = SettingsSingleton::getInstance().getCharacterType();
    tgui::Borders borders(10, 10, 10, 10);
    tgui::Color color(71, 255, 46);

    switch (current) {
        case 0: {
            character1->getRenderer()->setBorders(borders);
            character1->getRenderer()->setBorderColor(color);
        }
              break;
        case 1: {
            character2->getRenderer()->setBorders(borders);
            character2->getRenderer()->setBorderColor(color);
        }
              break;
        case 2: {
            character3->getRenderer()->setBorders(borders);
            character3->getRenderer()->setBorderColor(color);
        }
              break;
        case 3: {
            character4->getRenderer()->setBorders(borders);
            character4->getRenderer()->setBorderColor(color);
        }
              break;
        case 4: {
            character5->getRenderer()->setBorders(borders);
            character5->getRenderer()->setBorderColor(color);
        }
              break;
    }

}

void ChooseCharacterState::draw() {
    gui->draw();
}

bool ChooseCharacterState::update(sf::Time dt) {
    return true;
}

bool ChooseCharacterState::handleEvent(const sf::Event& event) {
    gui->handleEvent(event);
    return false;
}