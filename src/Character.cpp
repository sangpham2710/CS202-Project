#include "Character.hpp"

#include "Character.h"

Character::Character(float x, float y)
{
	hitBox.setSize(sf::Vector2f(x, y));
	texture.loadFromFile("Movement\\A1.png");
	hitBox.setTexture(&texture);
	up = 0;
	right = 0;
	down = 0;
	left = 0;
}

void Character::drawTo(sf::RenderWindow& window)
{
	window.draw(hitBox);
}

void Character::processEvents(sf::Keyboard::Key key, bool checkPressed)
{
	if (checkPressed == 1) {
		if (key == sf::Keyboard::W || key == sf::Keyboard::Up)
			up = 1;
		if (key == sf::Keyboard::A || key == sf::Keyboard::Left)
			left = 1;
		if (key == sf::Keyboard::S || key == sf::Keyboard::Down)
			down = 1;
		if (key == sf::Keyboard::D || key == sf::Keyboard::Right)
			right = 1;
	}
	if (checkPressed == 0) {
		up = 0;
		right = 0;
		down = 0;
		left = 0;
	}
}

void Character::update()
{
	sf::Vector2f movement;
	if (!up && !down && !right && !left) {
		changeTexture(-1);
		return;
	}
	if (up) {
		changeTexture(0);
		movement.y -= 0.5f;
	}
	if (down) {
		changeTexture(1);
		movement.y += 0.5f;
	}
	if (right) {
		changeTexture(3);
		movement.x += 0.5f;
	}
	if (left) {
		changeTexture(2);
		movement.x -= 0.5f;
	}
	hitBox.move(movement);
}

void Character::changeTexture(int type)
{
	int t = getPhaseTime();
	switch (type)
	{
	case 0://W
		if (t == 0) { texture.loadFromFile("Movement\\W1.png"); return; }
		if (t == 1) { texture.loadFromFile("Movement\\W2.png"); return; }
		if (t == 2) { texture.loadFromFile("Movement\\W3.png"); return; }
		if (t == 3) { texture.loadFromFile("Movement\\W4.png"); return; }
		if (t == 4) { texture.loadFromFile("Movement\\W5.png"); return; }
		break;
	case 1://S
		if (t == 0) { texture.loadFromFile("Movement\\S1.png"); return; }
		if (t == 1) { texture.loadFromFile("Movement\\S2.png"); return; }
		if (t == 2) { texture.loadFromFile("Movement\\S3.png"); return; }
		if (t == 3) { texture.loadFromFile("Movement\\S4.png"); return; }
		if (t == 4) { texture.loadFromFile("Movement\\S5.png"); return; }
		break;
	case 2://A
		if (t == 0) { texture.loadFromFile("Movement\\A1.png"); return; }
		if (t == 1) { texture.loadFromFile("Movement\\A2.png"); return; }
		if (t == 2) { texture.loadFromFile("Movement\\A3.png"); return; }
		if (t == 3) { texture.loadFromFile("Movement\\A4.png"); return; }
		if (t == 4) { texture.loadFromFile("Movement\\A5.png"); return; }
		break;
	case 3://D
		if (t == 0) { texture.loadFromFile("Movement\\D1.png"); return; }
		if (t == 1) { texture.loadFromFile("Movement\\D2.png"); return; }
		if (t == 2) { texture.loadFromFile("Movement\\D3.png"); return; }
		if (t == 3) { texture.loadFromFile("Movement\\D4.png"); return; }
		if (t == 4) { texture.loadFromFile("Movement\\D5.png"); return; }
		break;
	default:
		texture.loadFromFile("Movement\\S1.png");
		break;
	}
}

int Character::getPhaseTime()
{
	if (clock.getElapsedTime().asSeconds() < 0.1f) {
		return 0;
	}
	if (clock.getElapsedTime().asSeconds() > 0.1f && clock.getElapsedTime().asSeconds() < 0.2f) {
		return 1;
	}
	if (clock.getElapsedTime().asSeconds() > 0.2f && clock.getElapsedTime().asSeconds() < 0.3f) {
		return 2;
	}
	if (clock.getElapsedTime().asSeconds() > 0.3f && clock.getElapsedTime().asSeconds() < 0.4f) {
		return 3;
	}
	if (clock.getElapsedTime().asSeconds() > 0.4f) {
		clock.restart();
		return 4;
	}
}