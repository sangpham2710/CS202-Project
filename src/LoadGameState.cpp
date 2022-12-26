#include "LoadGameState.hpp"

#include "Constants.hpp"
#include "MusicPlayer.hpp"
#include "SoundNode.hpp"
#include "Utility.hpp"

LoadGameState::LoadGameState(StateStack& stack, Context context)
    : State(stack, context) {
    sf::RenderWindow& window = *getContext().window;
    gui->loadWidgetsFromFile("./assets/gui/load-game-state.txt");

    auto loadGameLabel = gui->get<tgui::Label>("loadGameLabel");
    auto inputLabel = gui->get<tgui::Label>("inputLabel");
    auto inputBox = gui->get<tgui::EditBox>("inputBox");
    auto statusLabel = gui->get<tgui::Label>("statusLabel");
    auto loadButton = gui->get<tgui::Button>("loadButton");
    auto backButton = gui->get<tgui::Button>("backButton");

    std::unique_ptr<SoundNode> soundNode(new SoundNode(*getContext().sounds));
    mSceneGraph.attachChild(std::move(soundNode));

    auto playBtnHoverSound = [&] {
        Command command;
        command.category = Category::SoundEffect;
        command.action =
            derivedAction<SoundNode>([&](SoundNode& node, sf::Time) {
            node.playSound(SoundEffect::ButtonHover,
                { 0.5 * Constants::SCREEN_WIDTH,
                 0.5 * Constants::SCREEN_HEIGHT });
                });
        mCommandQueue.push(command);
    };

    loadButton->onMouseEnter(playBtnHoverSound);
    backButton->onMouseEnter(playBtnHoverSound);

    alignCenter(loadGameLabel, window);
    alignCenter(inputLabel, window);
    alignCenter(inputBox, window);
    alignCenter(loadButton, window);
    alignCenter(backButton, window);
    
    statusLabel->setInheritedOpacity(0.0);

    backButton->onPress([&] { 
        requestStackPop();
    });
}
void LoadGameState::draw() {
    gui->draw();
}

bool LoadGameState::update(sf::Time dt) {
    while (!mCommandQueue.isEmpty()) {
        mSceneGraph.onCommand(mCommandQueue.pop(), dt);
    }

    return true;
}

bool LoadGameState::handleEvent(const sf::Event& event) {
    gui->handleEvent(event);
    return false;
}