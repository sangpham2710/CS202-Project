
#include <iostream>
#include <stdexcept>
#include <SFML/Graphics.hpp>
#include <string.h>
#include "Application.h"
using namespace std;

#define WIDTH_MAX 1024
#define HEIGHT_MAX 768
#define PIXEL 64

void printPath(sf::Sprite sprite, sf::RenderWindow& window, int& width, int& height) {
  sprite.setPosition(width, height);
  window.draw(sprite);
  height += PIXEL;
}

int main() {

  sf::RenderWindow window(sf::VideoMode({WIDTH_MAX, HEIGHT_MAX}), "SFML Project");
  sf::Event event;

   sf::Texture textureGrassPath1;
  textureGrassPath1.loadFromFile(
      "./assets/textures/background/grass-path-1.png");
  sf::Sprite spriteGrassPath1(textureGrassPath1);

  sf::Texture textureGrassPath2;
  textureGrassPath2.loadFromFile(
      "./assets/textures/background/grass-path-3.png");
  sf::Sprite spriteGrassPath2(textureGrassPath2);

  sf::Texture textureBush;
  textureBush.loadFromFile(
      "./assets/textures/background/bush-2.png");
  sf::Sprite spriteBush(textureBush);

  sf::Texture textureRiver;
  textureRiver.loadFromFile(
      "./assets/textures/background/river-1.png");
  sf::Sprite spriteRiver(textureRiver);

  sf::Texture textureRailway;
  textureRailway.loadFromFile(
      "./assets/textures/background/railway-1.png");
  sf::Sprite spriteRailway(textureRailway);

  sf::Texture textureRoadPathAbove;
  textureRoadPathAbove.loadFromFile(
      "./assets/textures/background/road-path-above.png");
  sf::Sprite spriteRoadPathAbove(textureRoadPathAbove);

  sf::Texture textureRoadPathAbove2;
  textureRoadPathAbove2.loadFromFile(
      "./assets/textures/background/road-path-above-2.png");
  sf::Sprite spriteRoadPathAbove2(textureRoadPathAbove2);

  sf::Texture textureRoadPathBelow;
  textureRoadPathBelow.loadFromFile(
      "./assets/textures/background/road-path-below.png");
  sf::Sprite spriteRoadPathBelow(textureRoadPathBelow);

  sf::Texture texturePavement;
  texturePavement.loadFromFile(
      "./assets/textures/background/pavement-1.png");
  sf::Sprite spritePavement;
  spritePavement.setTexture(texturePavement);

  sf::Texture texturePavement2;
  texturePavement2.loadFromFile("./assets/textures/background/pavement-2.png");
  sf::Sprite spritePavement2;
  spritePavement2.setTexture(texturePavement2);

  sf::Texture textureFireHydrant;
  textureFireHydrant.loadFromFile(
      "./assets/textures/background/fire-hydrant-1.png");
  sf::Sprite spriteFireHydrant(textureFireHydrant);

  sf::Texture textureLilyPad;
  textureLilyPad.loadFromFile(
      "./assets/textures/background/lily-pad-1.png");
  sf::Sprite spriteLilyPad(textureLilyPad);

  sf::Texture textureRoadPathMiddle;
  textureRoadPathMiddle.loadFromFile("./assets/textures/background/road-path-middle.png");
  sf::Sprite spriteRoadPathMiddle(textureRoadPathMiddle);

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) window.close();
    }

    window.clear();
    
    int width = 0;
    int height = 0;
    int countBlock = 0;
    while (width < WIDTH_MAX && height < HEIGHT_MAX) {
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

      printPath(spriteRailway, window, width, height);
      printPath(spriteRiver, window, width, height);
      printPath(spriteLilyPad, window, width, height);
      printPath(spriteRoadPathAbove, window, width, height);
      printPath(spriteRoadPathMiddle, window, width, height);
      printPath(spriteRoadPathBelow, window, width, height);

      spritePavement.setPosition(width, height);
      window.draw(spritePavement);
      if (countBlock == 7) {
        spriteFireHydrant.setPosition(width, height);
        window.draw(spriteFireHydrant);
      }
      height += 64;

      printPath(spritePavement2, window, width, height);
      printPath(spriteRoadPathAbove2, window, width, height);

      countBlock++;
      width += 64;
    }
    window.display();
  }
    return 0;
}