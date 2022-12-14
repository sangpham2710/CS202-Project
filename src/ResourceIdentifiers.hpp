#pragma once
// Forward declaration of SFML classes
namespace sf {
class Texture;
class Font;
class SoundBuffer;
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
    Grass,
    LilyPadAbove,
    LilyPadBelow,
    LilyPadSingle,
    PavementAbove,
    PavementBelow,
    Railway,
    WaterSingle,
    WaterAbove,
    WaterBelow,
    RoadSingle,
    RoadAbove,
    RoadBelow,
    RoadMiddle,
    Bush,
    FireHydrant,
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

namespace SoundEffect {
enum ID {
    Explosion,
    ButtonHover,
    ButtonClick,
};
}

namespace Music {
enum ID {
    MenuTheme,
    MissionTheme,
    LevelUpTheme,
    GameOverTheme,
};
}

// Forward declaration and a few type definitions
template <typename Resource, typename Identifier>
class ResourceHolder;

typedef ResourceHolder<sf::Texture, Textures::ID> TextureHolder;
typedef ResourceHolder<sf::Font, Fonts::ID> FontHolder;
typedef ResourceHolder<sf::SoundBuffer, SoundEffect::ID> SoundBufferHolder;