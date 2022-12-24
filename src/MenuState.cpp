#include "MenuState.hpp"

#include "Constants.hpp"
#include "MusicPlayer.hpp"
#include "SoundNode.hpp"
#include "Utility.hpp"

MenuState::MenuState(StateStack& stack, Context context)
    : State(stack, context), mSceneGraph(), mCommandQueue() {
    sf::RenderWindow& window = *getContext().window;
    gui->loadWidgetsFromFile("./assets/gui/menu-state.txt");

    auto menuLabel = gui->get<tgui::Label>("menuLabel");
    auto playBtn = gui->get<tgui::Button>("playButton");
    auto loadBtn = gui->get<tgui::Button>("loadButton");
    auto settingsBtn = gui->get<tgui::Button>("settingsButton");
    auto exitBtn = gui->get<tgui::Button>("exitButton");

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

    playBtn->onMouseEnter(playBtnHoverSound);
    loadBtn->onMouseEnter(playBtnHoverSound);
    settingsBtn->onMouseEnter(playBtnHoverSound);
    exitBtn->onMouseEnter(playBtnHoverSound);

    alignCenter(menuLabel, window);

    playBtn->onPress([&] {
        requestStackPop();
        requestStackPush(States::Game);
        requestStackPush(States::LevelUp);
    });
    alignCenter(playBtn, window);

    loadBtn->onPress([&] { requestStackPop(); });
    alignCenter(loadBtn, window);

    settingsBtn->onPress([&] { requestStackPush(States::Settings); });
    alignCenter(settingsBtn, window);

    exitBtn->onPress([&] { requestStackPop(); });
    alignCenter(exitBtn, window);

    context.music->play(Music::MenuTheme);
}

void MenuState::draw() {
    gui->draw();
}

bool MenuState::update(sf::Time dt) {
    while (!mCommandQueue.isEmpty()) {
        mSceneGraph.onCommand(mCommandQueue.pop(), dt);
    }
    return true;
}

bool MenuState::handleEvent(const sf::Event& event) {
    gui->handleEvent(event);
    return false;
}