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
    float mSpeed;
    Textures::ID texture;
};

std::vector<ObstacleData> initializeObstacleData();
std::vector<LaneData> initializeLaneData();