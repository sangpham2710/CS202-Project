#pragma once
// Forward declaration of SFML classes
namespace sf {
class Texture;
class Font;
}  // namespace sf

namespace Textures {
enum ID {
    Background,
    Character1Up,
    Character1Down,
    Character1Left,
    Character1Right,
    Character2Up,
    Character2Down,
    Character2Left,
    Character2Right,
    Character3Up,
    Character3Down,
    Character3Left,
    Character3Right,
    Character4Up,
    Character4Down,
    Character4Left,
    Character4Right,
    Character5Up,
    Character5Down,
    Character5Left,
    Character5Right,
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
