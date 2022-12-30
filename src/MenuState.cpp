#include "MenuState.hpp"

#include "Constants.hpp"
#include "MusicPlayer.hpp"
#include "SettingsSingleton.hpp"
#include "SoundNode.hpp"
#include "Utility.hpp"

MenuState::MenuState(StateStack& stack, Context context)
    : State(stack, context), mSceneGraph(), mCommandQueue() {
    sf::RenderWindow& window = *getContext().window;
    gui->loadWidgetsFromFile("./assets/gui/menu-state.txt");


#define menuLabel gui->get<tgui::Label>("menuLabel")
#define playButton gui->get<tgui::Button>("playButton")
#define loadButton gui->get<tgui::Button>("loadButton")
#define settingsButton gui->get<tgui::Button>("settingsButton")
#define exitButton gui->get<tgui::Button>("exitButton")

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

    playButton->onMouseEnter(playButtonHoverSound);
    playButton->onPress(playButtonClickSound);
    loadButton->onMouseEnter(playButtonHoverSound);
    loadButton->onPress(playButtonClickSound);

    settingsButton->onMouseEnter(playButtonHoverSound);
    settingsButton->onPress(playButtonClickSound);
    exitButton->onMouseEnter(playButtonHoverSound);
    exitButton->onPress(playButtonClickSound);


    alignCenter(menuLabel, window);

    playButton->onPress([&] {
        requestStackPop();
        SettingsSingleton::getInstance().setIsLevelLoaded(false);
        SettingsSingleton::getInstance().setCurrentLevelNumber(1);
        requestStackPush(States::Game);
        requestStackPush(States::LevelUp);
    });
    alignCenter(playButton, window);

    loadButton->onPress([&] { requestStackPush(States::LoadGame); });

    alignCenter(loadButton, window);

    settingsButton->onPress([&] { requestStackPush(States::Settings); });
    alignCenter(settingsButton, window);

    exitButton->onPress([&] { requestStackPop(); });
    alignCenter(exitButton, window);

    context.music->play(Music::MenuTheme);

#undef menuLabel
#undef playButton
#undef loadButton
#undef settingsButton
#undef exitButton
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