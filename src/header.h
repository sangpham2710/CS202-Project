#pragma once
// SFML libraries
#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
#include <string>
#include <string.h>
using namespace std;

class spriteRun {
public:
	sf::Sprite sprite;
	string str;
	int x, y;
	int speedrun;
public:
	spriteRun(sf::Texture& textureCar,int x, int y, int speed) {
		//sf::Texture textureCar;

		//if (!textureCar.loadFromFile(str))
		//{
		//	std::cerr << "Error while loading texture" << std::endl;
		//	return ;
		//}
		sprite.setTexture(textureCar);
		sf::FloatRect spriteCarSize = sprite.getGlobalBounds();
		sprite.setOrigin(spriteCarSize.width / 2., spriteCarSize.height / 2.);
		this->x = x; this->y = y;
		speedrun = speed;
		
	}
	void run(sf::RenderWindow& window) {
		x += speedrun;

		if (x - sprite.getTexture()->getSize().x < 0) x = window.getSize().x;
		if (x > (int)window.getSize().x + sprite.getTexture()->getSize().x) x = 0;
		if (y < 0) y = 0;
		if (y > (int)window.getSize().y) y = window.getSize().y;

		sprite.setPosition(x, y);
		window.draw(sprite);
	}
};