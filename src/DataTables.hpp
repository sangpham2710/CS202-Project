#pragma once

#include <functional>
#include <vector>

struct ObstacleData {
    Obstacle::Type mType;
    Textures::ID texture;
};

struct LaneData {
    Lane::Type mType;
    Lane::Direction mDirection;
    float mSpeed;
    Textures::ID texture;
};

std::vector<ObstacleData> initializeObstacleData();
std::vector<LaneData> initializeLaneData();