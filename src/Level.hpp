class Level
{
public:
	Level(int x);
	void levelUp();
	//~Level();
	//void saveLevel();
	//void loadLevel();
	float caculateSpeed();
	int caculateSpawnRate();

private:
	int level;
	int spawnRate;
	float speed;
	float percentScale;//max 100
	
};
