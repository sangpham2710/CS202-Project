#include "DataTables.hpp"
#include "Obstacle.hpp"
#include "Lane.hpp"

std::vector<ObstacleData> initializeObstacleData() {
	std::vector<ObstacleData> data(Obstacle::TypeCount);

	
	data[Obstacle::BlueBusLeft].texture = Textures::BlueBusLeft;

	
	data[Obstacle::BlueBusRight].texture = Textures::BlueBusRight;

	
	data[Obstacle::BlueCarLeft].texture = Textures::BlueCarLeft;

	
	data[Obstacle::BlueCarRight].texture = Textures::BlueCarRight;

	data[Obstacle::GrayCarLeft].texture = Textures::GrayCarLeft;

	data[Obstacle::GrayCarRight].texture = Textures::GrayCarRight;

	data[Obstacle::NewVanLeft].texture = Textures::NewVanLeft;

	data[Obstacle::NewVanRight].texture = Textures::NewVanRight;

	return data;
}

std::vector<LaneData> initializeLaneData() {
	return {};
}