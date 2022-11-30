#include "MenuState.hpp"

#include "Utility.hpp"

MenuState::MenuState(StateStack& stack, Context context)
    : State(stack, context) {
    mGameButton = tgui::Button::create();
    mGameButton->setTextSize(30);
    mGameButton->setText("Play Game");
    mGameButton->setPosition(100, 100);
    mGameButton->setSize(200, 100);
    mGameButton->onPress([&]() {
        requestStackPop();
        requestStackPush(States::Game);
    });
    gui->add(mGameButton);
    mSettingsButton = tgui::Button::create();
    mSettingsButton->setTextSize(30);
    mSettingsButton->setText("Settings");
    mSettingsButton->setPosition(100, 250);
    mSettingsButton->setSize(200, 100);
    mSettingsButton->onPress([&]() { requestStackPush(States::Settings); });
    gui->add(mSettingsButton);
    mExitButton = tgui::Button::create();
    mExitButton->setTextSize(30);
    mExitButton->setText("Exit");
    mExitButton->setPosition(100, 400);
    mExitButton->setSize(200, 100);
    mExitButton->onPress([&]() { requestStackPop(); });
    gui->add(mExitButton);
}

void MenuState::draw() {
    sf::RenderWindow& window = *getContext().window;

    sf::RectangleShape rectangle(sf::Vector2f(1024, 768));
    rectangle.setFillColor(sf::Color::Green);
    window.draw(rectangle);

    gui->draw();
}

bool MenuState::update(sf::Time dt) {
    return true;
}

bool MenuState::handleEvent(const sf::Event& event) {
    gui->handleEvent(event);
    return true;
}