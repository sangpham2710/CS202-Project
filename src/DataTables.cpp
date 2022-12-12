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
  std::vector<LaneData> data(Lane::TypeCount);
  
  data[Lane::Grass].texture = Textures::GrassLane;

  data[Lane::LilyPadAbove].texture = Textures::LilyPadAbove;

  data[Lane::LilyPadBelow].texture = Textures::LilyPadBelow;

  data[Lane::LilyPadSingle].texture = Textures::LilyPadSingle;

  data[Lane::PavementAbove].texture = Textures::PavementAbove;

  data[Lane::PavementBelow].texture = Textures::PavementBelow;

  data[Lane::Railway].texture = Textures::Railway;

  data[Lane::RoadAbove].texture = Textures::RoadAbove;

  data[Lane::RoadBelow].texture = Textures::RoadBelow;

  data[Lane::RoadMiddle].texture = Textures::RoadMiddle;

  data[Lane::RoadSingle].texture = Textures::RoadSingle;
	 
	return data;
}