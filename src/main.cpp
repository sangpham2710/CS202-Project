#include <iostream>
#include <stdexcept>
#include <SFML/Graphics.hpp>
#include "Application.h"

int main() {
  sf::RenderWindow window(sf::VideoMode({1800, 900}), "SFML Project");
  sf::Event event;

   sf::Texture textureGrassPath1;
  textureGrassPath1.loadFromFile(
      "D:/The University of Science/Semester "
      "4/CS202/Project/assets/textures/background/grass-path-1.png");
  sf::Sprite spriteGrassPath1(textureGrassPath1);

  sf::Texture textureGrassPath2;
  textureGrassPath2.loadFromFile(
      "D:/The University of Science/Semester "
      "4/CS202/Project/assets/textures/background/grass-path-3.png");
  sf::Sprite spriteGrassPath2(textureGrassPath2);

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) window.close();
    }

    window.clear();
    int widthMax = 1800;
    int heightMax = 900;
    int width = 0;
    int height = 0;
    int countBlock = 0;
    while (width < widthMax && height < heightMax) {
      height = 0;

      if (countBlock % 3 == 0) {
        spriteGrassPath1.setPosition(width, height);
        window.draw(spriteGrassPath1);
      } else {
        spriteGrassPath2.setPosition(width, height);
        window.draw(spriteGrassPath2);
      }
      height += 64;

      countBlock++;
      width += 64;
    }
    window.display();
  }
    return 0;
}