#include "PauseState.hpp"

#include "Constants.hpp"
#include "SettingsSingleton.hpp"
#include "SoundNode.hpp"
#include "Utility.hpp"

PauseState::PauseState(StateStack& stack, Context context)
    : State(stack, context), mSceneGraph(), mCommandQueue() {
    sf::RenderWindow& window = *getContext().window;
    gui->loadWidgetsFromFile("./assets/gui/pause-state.txt");

#define pauseLabel gui->get<tgui::Label>("pauseLabel")
#define continueButton gui->get<tgui::Button>("continueButton")
#define saveButton gui->get<tgui::Button>("saveButton")
#define settingsButton gui->get<tgui::Button>("settingsButton")
#define backToMenuButton gui->get<tgui::Button>("backToMenuButton")

    alignCenter(pauseLabel, window);
    alignCenter(continueButton, window);
    alignCenter(saveButton, window);
    alignCenter(settingsButton, window);
    alignCenter(backToMenuButton, window);

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

    continueButton->onMouseEnter(playButtonHoverSound);
    saveButton->onMouseEnter(playButtonHoverSound);
    settingsButton->onMouseEnter(playButtonHoverSound);
    backToMenuButton->onMouseEnter(playButtonHoverSound);


    continueButton->onPress([&] { requestStackPop(); });
    saveButton->onPress([&] {
        SettingsSingleton::getInstance().setIsLevelSaving(true);
        requestStackPop();
    });
    settingsButton->onPress([&] { requestStackPush(States::Settings); });

    backToMenuButton->onPress([&] {
        requestStateClear();
        requestStackPush(States::Menu);
    });

#undef pauseLabel
#undef continueButton
#undef saveButton
#undef settingsButton
#undef backToMenuButton
}

void PauseState::draw() {
    gui->draw();
}

bool PauseState::update(sf::Time dt) {
    while (!mCommandQueue.isEmpty()) {
        mSceneGraph.onCommand(mCommandQueue.pop(), dt);
    }
    return false;
}

bool PauseState::handleEvent(const sf::Event& event) {
    gui->handleEvent(event);
    return false;
}