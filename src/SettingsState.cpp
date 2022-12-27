#include "SettingsState.hpp"

#include "Constants.hpp"
#include "SettingsSingleton.hpp"
#include "SoundNode.hpp"
#include "Utility.hpp"

SettingsState::SettingsState(StateStack& stack, Context context)
    : State(stack, context), mSceneGraph(), mCommandQueue() {
    sf::RenderWindow& window = *getContext().window;
    gui->loadWidgetsFromFile("./assets/gui/settings-state.txt");

#define settingsLabel gui->get<tgui::Label>("settingsLabel")
#define soundLabel gui->get<tgui::Label>("soundLabel")
#define musicLabel gui->get<tgui::Label>("musicLabel")
#define soundSlider gui->get<tgui::Slider>("soundSlider")
#define musicSlider gui->get<tgui::Slider>("musicSlider")
#define soundGroup gui->get<tgui::Group>("soundGroup")
#define musicGroup gui->get<tgui::Group>("musicGroup")
#define characterButton gui->get<tgui::Button>("characterButton")
#define backButton gui->get<tgui::Button>("backButton")

    alignCenter(settingsLabel, window);
    alignCenter(soundGroup, window);
    alignCenter(musicGroup, window);
    alignCenter(characterButton, window);
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

    characterButton->onMouseEnter(playButtonHoverSound);
    backButton->onMouseEnter(playButtonHoverSound);

    characterButton->onPress(
        [&] { requestStackPush(States::ChooseCharacter); });

    backButton->onPress([&] { requestStackPop(); });

    soundSlider->setMinimum(0);
    soundSlider->setMaximum(100);

    musicSlider->setMinimum(0);
    musicSlider->setMaximum(100);

    soundSlider->setValue(SettingsSingleton::getInstance().getSoundVolume());
    musicSlider->setValue(SettingsSingleton::getInstance().getMusicVolume());

    soundSlider->onValueChange([&] {
        float value = gui->get<tgui::Slider>("soundSlider")->getValue();
        SettingsSingleton::getInstance().setSoundVolume(value);
    });

    musicSlider->onValueChange([&] {
        float value = gui->get<tgui::Slider>("musicSlider")->getValue();
        SettingsSingleton::getInstance().setMusicVolume(value);
    });
#undef settingsLabel
#undef soundLabel
#undef musicLabel
#undef soundSlider
#undef musicSlider
#undef soundGroup
#undef musicGroup
#undef characterButton
#undef backButton
}
void SettingsState::draw() {
    gui->draw();
}

bool SettingsState::update(sf::Time dt) {
    while (!mCommandQueue.isEmpty()) {
        mSceneGraph.onCommand(mCommandQueue.pop(), dt);
    }
    return true;
}

bool SettingsState::handleEvent(const sf::Event& event) {
    gui->handleEvent(event);
    return false;
}