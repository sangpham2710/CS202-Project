#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

class Character
{
public:
	Character(float x, float y);
	void drawTo(sf::RenderWindow& window);
	void processEvents(sf::Keyboard::Key key, bool checkPressed);
	void update();
	void changeTexture(int type);
	int getPhaseTime();

private:
	sf::Clock clock;
	sf::RectangleShape hitBox;
	sf::Texture texture;
	bool left, up, down, right;
};
