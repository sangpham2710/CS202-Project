#pragma once
// Forward declaration of SFML classes
namespace sf {
class Texture;
class Font;
}  // namespace sf

namespace Textures {
enum ID {
    Background,
    CharacterUp,
    CharacterDown,
    CharacterLeft,
    CharacterRight,
    BlueBusLeft,
    BlueBusRight,
    BlueCarLeft,
    BlueCarRight,
    GrayCarLeft,
    GrayCarRight,
    NewVanLeft,
    NewVanRight,
    OldVanLeft,
    OldVanRight,
    OrangeBusLeft,
    OrangeBusRight,
    PoliceCarLeft,
    PoliceCarRight,
    RedCarLeft,
    RedCarRight,
    RedStripedCarLeft,
    RedStripedCarRight,
    RedTruckLeft,
    RedTruckRight,
    SchoolBusLeft,
    SchoolBusRight,
    WhiteTruckLeft,
    WhiteTruckRight,
    YellowCabLeft,
    YellowCabRight,
    YellowCarLeft,
    YellowCarRight,
    GrassLane,
    LilyPadAbove,
    LilyPadBelow,
    LilyPadSingle,
    PavementAbove,
    PavementBelow,
    Railway,
    RoadSingle,
    Obstacle,
    River,
    RoadAbove,
    RoadBelow,
    RoadMiddle,
    Explosion,
    GreenLight,
    YellowLight,
    RedLight
};
}

namespace Fonts {
enum ID {
    Main,
};
}

// Forward declaration and a few type definitions
template <typename Resource, typename Identifier>
class ResourceHolder;

typedef ResourceHolder<sf::Texture, Textures::ID> TextureHolder;
typedef ResourceHolder<sf::Font, Fonts::ID> FontHolder;
