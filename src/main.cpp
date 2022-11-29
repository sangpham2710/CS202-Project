#include "Character.hpp"

int main() {
    sf::RenderWindow window(sf::VideoMode(1800, 900), "My Fucking Game");
    sf::Event event;

    Character character(50, 100);

    while (window.isOpen()) {
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed)
                character.processEvents(event.key.code, 1);

            if (event.type == sf::Event::KeyReleased)
                character.processEvents(event.key.code, 0);
        }
        window.clear(sf::Color::Yellow);
        character.update();
        character.drawTo(window);
        window.display();
    }
}