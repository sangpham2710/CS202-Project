#include "TexturesSingleton.hpp"

TexturesSingleton::TexturesSingleton() : mTextures() {
    mTextures.load(Textures::Background, "./assets/textures/background.png");
    mTextures.load(Textures::Character1Up,
        "./assets/textures/character/character-1/up.png");
    mTextures.load(Textures::Character1Down,
        "./assets/textures/character/character-1/down.png");
    mTextures.load(Textures::Character1Left,
        "./assets/textures/character/character-1/left.png");
    mTextures.load(Textures::Character1Right,
        "./assets/textures/character/character-1/right.png");
    mTextures.load(Textures::Character2Up,
        "./assets/textures/character/character-2/up.png");
    mTextures.load(Textures::Character2Down,
        "./assets/textures/character/character-2/down.png");
    mTextures.load(Textures::Character2Left,
        "./assets/textures/character/character-2/left.png");
    mTextures.load(Textures::Character2Right,
        "./assets/textures/character/character-2/right.png");
    mTextures.load(Textures::Character3Up,
        "./assets/textures/character/character-3/up.png");
    mTextures.load(Textures::Character3Down,
        "./assets/textures/character/character-3/down.png");
    mTextures.load(Textures::Character3Left,
        "./assets/textures/character/character-3/left.png");
    mTextures.load(Textures::Character3Right,
        "./assets/textures/character/character-3/right.png");
    mTextures.load(Textures::Character4Up,
        "./assets/textures/character/character-4/up.png");
    mTextures.load(Textures::Character4Down,
        "./assets/textures/character/character-4/down.png");
    mTextures.load(Textures::Character4Left,
        "./assets/textures/character/character-4/left.png");
    mTextures.load(Textures::Character4Right,
        "./assets/textures/character/character-4/right.png");
    mTextures.load(Textures::Character5Up,
        "./assets/textures/character/character-5/up.png");
    mTextures.load(Textures::Character5Down,
        "./assets/textures/character/character-5/down.png");
    mTextures.load(Textures::Character5Left,
        "./assets/textures/character/character-5/left.png");
    mTextures.load(Textures::Character5Right,
        "./assets/textures/character/character-5/right.png");
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
    mTextures.load(Textures::GrassLane, "./assets/textures/lanes/grass.png");
    mTextures.load(Textures::Railway, "./assets/textures/lanes/railway.png");
    mTextures.load(Textures::River,
                   "./assets/textures/objects/river-single.png");
    mTextures.load(Textures::RoadAbove,
                   "./assets/textures/lanes/road-above.png");
    mTextures.load(Textures::RoadBelow,
                   "./assets/textures/lanes/road-below.png");
    mTextures.load(Textures::RoadMiddle,
                   "./assets/textures/lanes/road-middle.png");
    mTextures.load(Textures::PavementAbove,
                   "./assets/textures/lanes/pavement-above.png");
    mTextures.load(Textures::PavementBelow,
                   "./assets/textures/lanes/pavement-below.png");
    mTextures.load(Textures::LilyPadAbove,
                   "./assets/textures/lanes/lily-pad-above.png");
    mTextures.load(Textures::LilyPadBelow,
                   "./assets/textures/lanes/lily-pad-below.png");
    mTextures.load(Textures::LilyPadSingle,
                   "./assets/textures/lanes/lily-pad-single.png");
    mTextures.load(Textures::Bush,
                   "./assets/textures/objects/bush.png");
    mTextures.load(Textures::FireHydrant,
                   "./assets/textures/objects/fire-hydrant.png");
    mTextures.load(Textures::Explosion, "./assets/textures/explosion.png");
    mTextures.load(Textures::GreenLight, 
                    "./assets/textures/objects/green-light.png");
    mTextures.load(Textures::YellowLight,
                    "./assets/textures/objects/yellow-light.png");
    mTextures.load(Textures::RedLight,
                    "./assets/textures/objects/red-light.png");

}

TexturesSingleton& TexturesSingleton::getInstance() {
    static TexturesSingleton instance;
    return instance;
}

TextureHolder& TexturesSingleton::getTextures() {
    return mTextures;
}
