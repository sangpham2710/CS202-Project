#pragma once
// Forward declaration of SFML classes
namespace sf {
class Texture;
class Font;
}  // namespace sf

namespace Textures {
enum ID {
    Background,
    Character,
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
    Railway,
    RoadSingle,
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