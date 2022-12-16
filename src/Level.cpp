#include "Level.hpp"

Level::Level(int x)
{
	level = x;
	percentScale = 50;
}

void Level::levelUp()
{
	++level;
}

void Level::setSpeed(float& speed)
{
	speed = speed + level * percentScale;
}