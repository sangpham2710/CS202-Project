#pragma once

// Entity/scene node category, used to dispatch commands
namespace Category {
enum Type {
    None = 0,
    RoadLayer = 1 << 0,
    PlayerCharacter = 1 << 1,
    Obstacle = 1 << 2,
    Pickup = 1 << 3,
};
}
