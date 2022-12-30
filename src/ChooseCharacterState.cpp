#include "ChooseCharacterState.hpp"

#include "Constants.hpp"
#include "SoundNode.hpp"
#include "Utility.hpp"

ChooseCharacterState::ChooseCharacterState(StateStack& stack, Context context)
    : State(stack, context), mSceneGraph(), mCommandQueue() {
    sf::RenderWindow& window = *getContext().window;
    gui->loadWidgetsFromFile("./assets/gui/choose-character-state.txt");

#define characterLabel gui->get<tgui::Label>("characterLabel")
#define character1 gui->get<tgui::Button>("character1")
#define character2 gui->get<tgui::Button>("character2")
#define character3 gui->get<tgui::Button>("character3")
#define character4 gui->get<tgui::Button>("character4")
#define character5 gui->get<tgui::Button>("character5")
#define backButton gui->get<tgui::Button>("backButton")

    alignCenter(characterLabel, window);
    alignCenter(backButton, window);

    std::unique_ptr<SoundNode> soundNode(new SoundNode(*getContext().sounds));
    mSceneGraph.attachChild(std::move(soundNode));

    auto playButtonHoverSound = [&] {
        Command command;
        command.category = Category::SoundEffect;
        command.action =
            derivedAction<SoundNode>([&](SoundNode& node, sf::Time) {
                node.playSound(SoundEffect::ButtonHover,
                               {0.5 * Constants::SCREEN_WIDTH,
                                0.5 * Constants::SCREEN_HEIGHT});
            });
        mCommandQueue.push(command);
    };

    auto playButtonClickSound = [&] {
        Command command;
        command.category = Category::SoundEffect;
        command.action =
            derivedAction<SoundNode>([&](SoundNode& node, sf::Time) {
            node.playSound(SoundEffect::ButtonClick,
                { 0.5 * Constants::SCREEN_WIDTH,
                 0.5 * Constants::SCREEN_HEIGHT });
                });
        mCommandQueue.push(command);
    };

    backButton->onMouseEnter(playButtonHoverSound);
 

    backButton->onPress([&] {requestStackPop(); });

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
        } break;
        case 1: {
            character2->getRenderer()->setBorders(borders);
            character2->getRenderer()->setBorderColor(color);
        } break;
        case 2: {
            character3->getRenderer()->setBorders(borders);
            character3->getRenderer()->setBorderColor(color);
        } break;
        case 3: {
            character4->getRenderer()->setBorders(borders);
            character4->getRenderer()->setBorderColor(color);
        } break;
        case 4: {
            character5->getRenderer()->setBorders(borders);
            character5->getRenderer()->setBorderColor(color);
        } break;
    }

#undef characterLabel
#undef character1
#undef character2
#undef character3
#undef character4
#undef character5
#undef backButton
}

void ChooseCharacterState::draw() {
    gui->draw();
}

bool ChooseCharacterState::update(sf::Time dt) {
    while (!mCommandQueue.isEmpty()) {
        mSceneGraph.onCommand(mCommandQueue.pop(), dt);
    }
    return true;
}

bool ChooseCharacterState::handleEvent(const sf::Event& event) {
    gui->handleEvent(event);
    return false;
}