#include "DataTables.hpp"
#include "Obstacle.hpp"
#include "Lane.hpp"

std::vector<ObstacleData> initializeObstacleData() {
	std::vector<ObstacleData> data((unsigned)Obstacle::Type::TypeCount * 2);
	
	data[(unsigned)Obstacle::Type::BlueBus].texture = Textures::BlueBusLeft;

	data[(unsigned)Obstacle::Type::BlueBus + (unsigned)Obstacle::Type::TypeCount].texture = Textures::BlueBusRight;
	
	data[(unsigned)Obstacle::Type::BlueCar].texture = Textures::BlueCarLeft;
	
	data[(unsigned)Obstacle::Type::BlueCar + (unsigned)Obstacle::Type::TypeCount].texture = Textures::BlueCarRight;

	data[(unsigned)Obstacle::Type::GrayCar].texture = Textures::GrayCarLeft;

	data[(unsigned)Obstacle::Type::GrayCar + (unsigned)Obstacle::Type::TypeCount].texture = Textures::GrayCarRight;

	data[(unsigned)Obstacle::Type::NewVan].texture = Textures::NewVanLeft;

	data[(unsigned)Obstacle::Type::NewVan + (unsigned)Obstacle::Type::TypeCount].texture = Textures::NewVanRight;

	data[(unsigned)Obstacle::Type::OldVan].texture = Textures::OldVanLeft;

	data[(unsigned)Obstacle::Type::OldVan + (unsigned)Obstacle::Type::TypeCount].texture = Textures::OldVanRight;

	data[(unsigned)Obstacle::Type::OrangeBus].texture = Textures::OrangeBusLeft;

	data[(unsigned)Obstacle::Type::OrangeBus + (unsigned)Obstacle::Type::TypeCount].texture = Textures::OrangeBusRight;

	data[(unsigned)Obstacle::Type::PoliceCar].texture = Textures::PoliceCarLeft;

	data[(unsigned)Obstacle::Type::PoliceCar + (unsigned)Obstacle::Type::TypeCount].texture = Textures::PoliceCarRight;

	data[(unsigned)Obstacle::Type::RedCar].texture = Textures::RedCarLeft;

	data[(unsigned)Obstacle::Type::RedStripedCar].texture = Textures::RedStripedCarLeft;

	data[(unsigned)Obstacle::Type::RedStripedCar + (unsigned)Obstacle::Type::TypeCount].texture = Textures::RedStripedCarRight;

	data[(unsigned)Obstacle::Type::RedTruck].texture = Textures::RedTruckLeft;

	data[(unsigned)Obstacle::Type::RedTruck + (unsigned)Obstacle::Type::TypeCount].texture = Textures::RedTruckRight;

	data[(unsigned)Obstacle::Type::SchoolBus].texture = Textures::SchoolBusLeft;

	data[(unsigned)Obstacle::Type::SchoolBus + (unsigned)Obstacle::Type::TypeCount].texture = Textures::SchoolBusRight;

	data[(unsigned)Obstacle::Type::WhiteTruck].texture = Textures::WhiteTruckLeft;

	data[(unsigned)Obstacle::Type::WhiteTruck + (unsigned)Obstacle::Type::TypeCount].texture = Textures::WhiteTruckRight;

	data[(unsigned)Obstacle::Type::YellowCab].texture = Textures::YellowCabLeft;

	data[(unsigned)Obstacle::Type::YellowCab + (unsigned)Obstacle::Type::TypeCount].texture = Textures::YellowCabRight;

	data[(unsigned)Obstacle::Type::YellowCar].texture = Textures::YellowCarLeft;

	data[(unsigned)Obstacle::Type::YellowCar + (unsigned)Obstacle::Type::TypeCount].texture = Textures::YellowCarRight;

	return data;
}

std::vector<LaneData> initializeLaneData() {
	return {};
}