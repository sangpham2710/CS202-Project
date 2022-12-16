#pragma once

#include "ResourceIdentifiers.hpp"
#include <functional>
#include <vector>

class Obstacle;
class Lane;

struct ObstacleData {
    Textures::ID texture;
};

struct LaneData {
    Textures::ID texture;
};

struct characterData {
    Textures::ID texture;
};
std::vector<ObstacleData> initializeObstacleData();
std::vector<LaneData> initializeLaneData();
std::vector<characterData> initializeCharacterData();