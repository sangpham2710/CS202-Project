
#include "PauseState.hpp"

#include "Constants.hpp"
#include "SoundNode.hpp"
#include "Utility.hpp"

PauseState::PauseState(StateStack& stack, Context context)
    : State(stack, context), mSceneGraph(), mCommandQueue() {
    sf::RenderWindow& window = *getContext().window;
    gui->loadWidgetsFromFile("./assets/gui/pause-state.txt");

    auto pauseLabel = gui->get<tgui::Label>("pauseLabel");
    auto continueBtn = gui->get<tgui::Button>("continueButton");
    auto saveBtn = gui->get<tgui::Button>("saveButton");
    auto settingsBtn = gui->get<tgui::Button>("settingsButton");
    auto backToMenuBtn = gui->get<tgui::Button>("backToMenuButton");

    alignCenter(pauseLabel, window);
    alignCenter(continueBtn, window);
    alignCenter(saveBtn, window);
    alignCenter(settingsBtn, window);
    alignCenter(backToMenuBtn, window);

    std::unique_ptr<SoundNode> soundNode(new SoundNode(*getContext().sounds));
    mSceneGraph.attachChild(std::move(soundNode));

    auto playBtnHoverSound = [&] {
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

    continueBtn->onMouseEnter(playBtnHoverSound);
    saveBtn->onMouseEnter(playBtnHoverSound);
    settingsBtn->onMouseEnter(playBtnHoverSound);
    backToMenuBtn->onMouseEnter(playBtnHoverSound);


    continueBtn->onPress([&] { requestStackPop(); });
    saveBtn->onPress([&] { requestStackPush(States::Menu); });
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
    while (!mCommandQueue.isEmpty()) {
        mSceneGraph.onCommand(mCommandQueue.pop(), dt);
    }
    return false;
}

bool PauseState::handleEvent(const sf::Event& event) {
    gui->handleEvent(event);
    return false;
}