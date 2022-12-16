#include "Level.hpp"

Level::Level(int x)
{
	level = x;
	percentScale = 50;
	speed = 100;
	spawnRate = 10;
}

void Level::levelUp()
{
	++level;
}

float Level::caculateSpeed()
{
	return (speed + level * percentScale);
}

int Level::caculateSpawnRate()
{
	return spawnRate + level*20;
}