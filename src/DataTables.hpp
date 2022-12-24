#pragma once

#include <functional>
#include <map>
#include <vector>

#include "ResourceIdentifiers.hpp"

struct ObstacleData {
    Textures::ID texture;
};

struct LaneData {
    Textures::ID texture;
};

struct CharacterData {
    Textures::ID texture;
};

std::vector<ObstacleData> initializeObstacleData();
std::vector<LaneData> initializeLaneData();
std::vector<CharacterData> initializeCharacterData();