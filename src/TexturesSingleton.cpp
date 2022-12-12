#include "TexturesSingleton.hpp"

TexturesSingleton::TexturesSingleton() : mTextures() {
    mTextures.load(Textures::Background, "./assets/textures/background.png");
    mTextures.load(Textures::CharacterUp, "./assets/textures/character/Skin1Up.png");
    mTextures.load(Textures::CharacterDown, "./assets/textures/character/Skin1Down.png");
    mTextures.load(Textures::CharacterLeft, "./assets/textures/character/Skin1Left.png");
    mTextures.load(Textures::CharacterRight, "./assets/textures/character/Skin1Right.png");
    mTextures.load(Textures::BlueBusLeft,
                   "./assets/textures/vehicles/blue-bus-left.png");
    mTextures.load(Textures::BlueBusRight,
                   "./assets/textures/vehicles/blue-bus-right.png");
    mTextures.load(Textures::BlueCarLeft,
                   "./assets/textures/vehicles/blue-car-left.png");
    mTextures.load(Textures::BlueCarRight,
                   "./assets/textures/vehicles/blue-car-right.png");
    mTextures.load(Textures::GrayCarLeft,
                   "./assets/textures/vehicles/gray-car-left.png");
    mTextures.load(Textures::GrayCarRight,
                   "./assets/textures/vehicles/gray-car-right.png");
    mTextures.load(Textures::NewVanLeft,
                   "./assets/textures/vehicles/new-van-left.png");
    mTextures.load(Textures::NewVanRight,
                   "./assets/textures/vehicles/new-van-right.png");
    mTextures.load(Textures::OldVanLeft,
                   "./assets/textures/vehicles/old-van-left.png");
    mTextures.load(Textures::OldVanRight,
                   "./assets/textures/vehicles/old-van-right.png");
    mTextures.load(Textures::OrangeBusLeft,
                   "./assets/textures/vehicles/orange-bus-left.png");
    mTextures.load(Textures::OrangeBusRight,
                   "./assets/textures/vehicles/orange-bus-right.png");
    mTextures.load(Textures::PoliceCarLeft,
                   "./assets/textures/vehicles/police-car-left.png");
    mTextures.load(Textures::PoliceCarRight,
                   "./assets/textures/vehicles/police-car-right.png");
    mTextures.load(Textures::RedCarLeft,
                   "./assets/textures/vehicles/red-car-left.png");
    mTextures.load(Textures::RedCarRight,
                   "./assets/textures/vehicles/red-car-right.png");
    mTextures.load(Textures::RedStripedCarLeft,
                   "./assets/textures/vehicles/red-striped-car-left.png");
    mTextures.load(Textures::RedStripedCarRight,
                   "./assets/textures/vehicles/red-striped-car-right.png");
    mTextures.load(Textures::RedTruckLeft,
                   "./assets/textures/vehicles/red-truck-left.png");
    mTextures.load(Textures::RedTruckRight,
                   "./assets/textures/vehicles/red-truck-right.png");
    mTextures.load(Textures::SchoolBusLeft,
                   "./assets/textures/vehicles/school-bus-left.png");
    mTextures.load(Textures::SchoolBusRight,
                   "./assets/textures/vehicles/school-bus-right.png");
    mTextures.load(Textures::WhiteTruckLeft,
                   "./assets/textures/vehicles/white-truck-left.png");
    mTextures.load(Textures::WhiteTruckRight,
                   "./assets/textures/vehicles/white-truck-right.png");
    mTextures.load(Textures::YellowCabLeft,
                   "./assets/textures/vehicles/yellow-cab-left.png");
    mTextures.load(Textures::YellowCabRight,
                   "./assets/textures/vehicles/yellow-cab-right.png");
    mTextures.load(Textures::YellowCarLeft,
                   "./assets/textures/vehicles/yellow-car-left.png");
    mTextures.load(Textures::YellowCarRight,
                   "./assets/textures/vehicles/yellow-car-right.png");
    mTextures.load(Textures::RoadSingle,
                   "./assets/textures/lanes/road-single.png");
    mTextures.load(Textures::Obstacle,
                   "./assets/textures/vehicles/blue-bus-left.png");
    mTextures.load(Textures::GrassLane, "./assets/textures/lanes/grass.png");
    mTextures.load(Textures::Railway, "./assets/textures/lanes/railway.png");
    mTextures.load(Textures::River, "./assets/textures/objects/river-single.png");
    mTextures.load(Textures::RoadAbove, "./assets/textures/lanes/road-above.png");
    mTextures.load(Textures::RoadBelow, "./assets/textures/lanes/road-below.png");
    mTextures.load(Textures::RoadMiddle, "./assets/textures/lanes/road-middle.png");
    mTextures.load(Textures::PavementAbove, "./assets/textures/lanes/pavement-above.png");
    mTextures.load(Textures::PavementBelow,
                   "./assets/textures/lanes/pavement-below.png");
    mTextures.load(Textures::LilyPadAbove,
                   "./assets/textures/lanes/lily-pad-above.png");
    mTextures.load(Textures::LilyPadBelow,
                   "./assets/textures/lanes/lily-pad-below.png");
    mTextures.load(Textures::LilyPadSingle, "./assets/textures/lanes/lily-pad-single.png");
}

TexturesSingleton& TexturesSingleton::getInstance() {
    static TexturesSingleton instance;
    return instance;
}

TextureHolder& TexturesSingleton::getTextures() {
    return mTextures;
}
