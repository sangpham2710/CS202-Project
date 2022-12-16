#include "World.hpp"

class Level
{
public:
	Level(int x);
	void levelUp();
	//~Level();
	//void saveLevel();
	//void loadLevel();
	void setSpeed(float& speed);
	//void changeSpawnRate();

private:
	int level;
	float percentScale;//max 100
	//std::vector<std::unique_ptr<Lane>> lanes;
};
