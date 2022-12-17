#include "DataTables.hpp"

#include "Character.hpp"
#include "Lane.hpp"
#include "Obstacle.hpp"

std::vector<ObstacleData> initializeObstacleData() {
    std::vector<ObstacleData> data((unsigned)Obstacle::Type::TypeCount * 2);

    data[(unsigned)Obstacle::Type::BlueBus].texture = Textures::BlueBusLeft;

    data[(unsigned)Obstacle::Type::BlueBus +
         (unsigned)Obstacle::Type::TypeCount]
        .texture = Textures::BlueBusRight;

    data[(unsigned)Obstacle::Type::BlueCar].texture = Textures::BlueCarLeft;

    data[(unsigned)Obstacle::Type::BlueCar +
         (unsigned)Obstacle::Type::TypeCount]
        .texture = Textures::BlueCarRight;

    data[(unsigned)Obstacle::Type::GrayCar].texture = Textures::GrayCarLeft;

    data[(unsigned)Obstacle::Type::GrayCar +
         (unsigned)Obstacle::Type::TypeCount]
        .texture = Textures::GrayCarRight;

    data[(unsigned)Obstacle::Type::NewVan].texture = Textures::NewVanLeft;

    data[(unsigned)Obstacle::Type::NewVan + (unsigned)Obstacle::Type::TypeCount]
        .texture = Textures::NewVanRight;

    data[(unsigned)Obstacle::Type::OldVan].texture = Textures::OldVanLeft;

    data[(unsigned)Obstacle::Type::OldVan + (unsigned)Obstacle::Type::TypeCount]
        .texture = Textures::OldVanRight;

    data[(unsigned)Obstacle::Type::OrangeBus].texture = Textures::OrangeBusLeft;

    data[(unsigned)Obstacle::Type::OrangeBus +
         (unsigned)Obstacle::Type::TypeCount]
        .texture = Textures::OrangeBusRight;

    data[(unsigned)Obstacle::Type::PoliceCar].texture = Textures::PoliceCarLeft;

    data[(unsigned)Obstacle::Type::PoliceCar +
         (unsigned)Obstacle::Type::TypeCount]
        .texture = Textures::PoliceCarRight;

    data[(unsigned)Obstacle::Type::RedCar].texture = Textures::RedCarLeft;
    data[(unsigned)Obstacle::Type::RedCar + (unsigned)Obstacle::Type::TypeCount]
        .texture = Textures::RedCarRight;

    data[(unsigned)Obstacle::Type::RedStripedCar].texture =
        Textures::RedStripedCarLeft;

    data[(unsigned)Obstacle::Type::RedStripedCar +
         (unsigned)Obstacle::Type::TypeCount]
        .texture = Textures::RedStripedCarRight;

    data[(unsigned)Obstacle::Type::RedTruck].texture = Textures::RedTruckLeft;

    data[(unsigned)Obstacle::Type::RedTruck +
         (unsigned)Obstacle::Type::TypeCount]
        .texture = Textures::RedTruckRight;

    data[(unsigned)Obstacle::Type::SchoolBus].texture = Textures::SchoolBusLeft;

    data[(unsigned)Obstacle::Type::SchoolBus +
         (unsigned)Obstacle::Type::TypeCount]
        .texture = Textures::SchoolBusRight;

    data[(unsigned)Obstacle::Type::WhiteTruck].texture =
        Textures::WhiteTruckLeft;

    data[(unsigned)Obstacle::Type::WhiteTruck +
         (unsigned)Obstacle::Type::TypeCount]
        .texture = Textures::WhiteTruckRight;

    data[(unsigned)Obstacle::Type::YellowCab].texture = Textures::YellowCabLeft;

    data[(unsigned)Obstacle::Type::YellowCab +
         (unsigned)Obstacle::Type::TypeCount]
        .texture = Textures::YellowCabRight;

    data[(unsigned)Obstacle::Type::YellowCar].texture = Textures::YellowCarLeft;

    data[(unsigned)Obstacle::Type::YellowCar +
         (unsigned)Obstacle::Type::TypeCount]
        .texture = Textures::YellowCarRight;

    data[(unsigned)Obstacle::Type::Bush].texture = Textures::Bush;
    data[(unsigned)Obstacle::Type::FireHydrant].texture = Textures::FireHydrant;
    data[(unsigned)Obstacle::Type::WaterSingle].texture = Textures::WaterSingle;
    data[(unsigned)Obstacle::Type::WaterAbove].texture = Textures::WaterAbove;
    data[(unsigned)Obstacle::Type::WaterBelow].texture = Textures::WaterBelow;
    return data;
}

std::vector<LaneData> initializeLaneData() {
    std::vector<LaneData> data((unsigned)Lane::TextureType::TypeCount);

    data[(unsigned)Lane::TextureType::Grass].texture = Textures::Grass;

    data[(unsigned)Lane::TextureType::LilyPadAbove].texture =
        Textures::LilyPadAbove;

    data[(unsigned)Lane::TextureType::LilyPadBelow].texture =
        Textures::LilyPadBelow;

    data[(unsigned)Lane::TextureType::LilyPadSingle].texture =
        Textures::LilyPadSingle;

    data[(unsigned)Lane::TextureType::PavementAbove].texture =
        Textures::PavementAbove;

    data[(unsigned)Lane::TextureType::PavementBelow].texture =
        Textures::PavementBelow;

    data[(unsigned)Lane::TextureType::Railway].texture = Textures::Railway;

    data[(unsigned)Lane::TextureType::RoadAbove].texture = Textures::RoadAbove;

    data[(unsigned)Lane::TextureType::RoadBelow].texture = Textures::RoadBelow;

    data[(unsigned)Lane::TextureType::RoadMiddle].texture =
        Textures::RoadMiddle;

    data[(unsigned)Lane::TextureType::RoadSingle].texture =
        Textures::RoadSingle;

    return data;
}

std::vector<CharacterData> initializeCharacterData() {
    std::vector<CharacterData> data((unsigned)Character::Direction::TypeCount *
                                    5);

    data[(unsigned)Character::Direction::CharacterUp].texture =
        Textures::Character1Up;
    data[(unsigned)Character::Direction::CharacterDown].texture =
        Textures::Character1Down;
    data[(unsigned)Character::Direction::CharacterLeft].texture =
        Textures::Character1Left;
    data[(unsigned)Character::Direction::CharacterRight].texture =
        Textures::Character1Right;

    data[(unsigned)Character::Direction::CharacterUp +
         (unsigned)Character::Direction::TypeCount]
        .texture = Textures::Character2Up;
    data[(unsigned)Character::Direction::CharacterDown +
         (unsigned)Character::Direction::TypeCount]
        .texture = Textures::Character2Down;
    data[(unsigned)Character::Direction::CharacterLeft +
         (unsigned)Character::Direction::TypeCount]
        .texture = Textures::Character2Left;
    data[(unsigned)Character::Direction::CharacterRight +
         (unsigned)Character::Direction::TypeCount]
        .texture = Textures::Character2Right;

    data[(unsigned)Character::Direction::CharacterUp +
         (unsigned)Character::Direction::TypeCount * 2]
        .texture = Textures::Character3Up;
    data[(unsigned)Character::Direction::CharacterDown +
         (unsigned)Character::Direction::TypeCount * 2]
        .texture = Textures::Character3Down;
    data[(unsigned)Character::Direction::CharacterLeft +
         (unsigned)Character::Direction::TypeCount * 2]
        .texture = Textures::Character3Left;
    data[(unsigned)Character::Direction::CharacterRight +
         (unsigned)Character::Direction::TypeCount * 2]
        .texture = Textures::Character3Right;

    data[(unsigned)Character::Direction::CharacterUp +
         (unsigned)Character::Direction::TypeCount * 3]
        .texture = Textures::Character4Up;
    data[(unsigned)Character::Direction::CharacterDown +
         (unsigned)Character::Direction::TypeCount * 3]
        .texture = Textures::Character4Down;
    data[(unsigned)Character::Direction::CharacterLeft +
         (unsigned)Character::Direction::TypeCount * 3]
        .texture = Textures::Character4Left;
    data[(unsigned)Character::Direction::CharacterRight +
         (unsigned)Character::Direction::TypeCount * 3]
        .texture = Textures::Character4Right;

    data[(unsigned)Character::Direction::CharacterUp +
         (unsigned)Character::Direction::TypeCount * 4]
        .texture = Textures::Character5Up;
    data[(unsigned)Character::Direction::CharacterDown +
         (unsigned)Character::Direction::TypeCount * 4]
        .texture = Textures::Character5Down;
    data[(unsigned)Character::Direction::CharacterLeft +
         (unsigned)Character::Direction::TypeCount * 4]
        .texture = Textures::Character5Left;
    data[(unsigned)Character::Direction::CharacterRight +
         (unsigned)Character::Direction::TypeCount * 4]
        .texture = Textures::Character5Right;

    return data;
}
