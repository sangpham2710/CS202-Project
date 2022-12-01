#include "MenuState.hpp"

#include "Utility.hpp"

MenuState::MenuState(StateStack& stack, Context context)
    : State(stack, context) {

    gui->loadWidgetsFromFile("./assets/gui/menu-state.txt");

    gui->setFont("./assets/Sansation.ttf");

    gui->get<tgui::Button>("playButton")->onPress([&] {
        requestStackPop();
        requestStackPush(States::Game);
    });

    gui->get<tgui::Button>("settingButton")->onPress([&] {
        requestStackPush(States::Settings);
    });

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