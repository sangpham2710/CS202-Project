#include <iostream>
#include <stdexcept>
#include <SFML/Graphics.hpp>
#include "Application.h"

int main() {
  sf::RenderWindow window(sf::VideoMode({800, 600}), "SFML Project");
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

  sf::Texture textureBush;
  textureBush.loadFromFile(
      "D:/The University of Science/Semester "
      "4/CS202/Project/assets/textures/background/bush-1.png");
  sf::Sprite spriteBush(textureBush);

  sf::Texture textureRiver;
  textureRiver.loadFromFile(
      "D:/The University of Science/Semester "
      "4/CS202/Project/assets/textures/background/river-1.png");
  sf::Sprite spriteRiver(textureRiver);

  sf::Texture textureRailway;
  textureRailway.loadFromFile(
      "D:/The University of Science/Semester "
      "4/CS202/Project/assets/textures/background/railway-1.png");
  sf::Sprite spriteRailway(textureRailway);

  sf::Texture textureRoadPathAbove;
  textureRoadPathAbove.loadFromFile(
      "D:/The University of Science/Semester "
      "4/CS202/Project/assets/textures/background/road-path-above.png");
  sf::Sprite spriteRoadPathAbove(textureRoadPathAbove);

  sf::Texture textureRoadPathBelow;
  textureRoadPathBelow.loadFromFile(
      "D:/The University of Science/Semester "
      "4/CS202/Project/assets/textures/background/road-path-below.png");
  sf::Sprite spriteRoadPathBelow(textureRoadPathBelow);



  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) window.close();
    }

    window.clear();
    int widthMax = 800;
    int heightMax = 600;
    int width = 0;
    int height = 0;
    int countBlock = 0;
    while (width < widthMax && height < heightMax) {
      height = 0;

      if (countBlock % 3 == 0) {
        spriteGrassPath2.setPosition(width, height);
        window.draw(spriteGrassPath2);
        spriteBush.setPosition(width, height);
        window.draw(spriteBush);
      } else {
        spriteGrassPath1.setPosition(width, height);
        window.draw(spriteGrassPath1);
      }
      height += 64;

      spriteRailway.setPosition(width, height);
      window.draw(spriteRailway);
      height += 64;

      spriteRiver.setPosition(width, height);
      window.draw(spriteRiver);
      height += 64;

      spriteRoadPathAbove.setPosition(width, height);
      window.draw(spriteRoadPathAbove);
      height += 64;
      spriteRoadPathBelow.setPosition(width, height);
      window.draw(spriteRoadPathBelow);
      height += 64;

      countBlock++;
      width += 64;
    }
    window.display();
  }
    return 0;
}