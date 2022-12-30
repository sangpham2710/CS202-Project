#pragma once

#include <array>
#include <map>
#include <string>
#include <vector>

#include "Lane.hpp"
#include "SceneNode.hpp"

class LevelManager {
   public:
    LevelManager();
    LevelManager(SceneNode* levelNode);

    void setLevelNode(SceneNode* levelNode);

    void generateLevel(int levelNumber);
    void saveLevel() const;
    void loadLevel(const std::string& filename);
    void prepareLevel(int levelNumber);
    float calcLevelObstacleSpeed(int levelNumber) const;
    int calcLevelMinObstacleSpawnRate(int levelNumber) const;
    int calcLevelMaxObstacleSpawnRate(int levelNumber) const;
    float getLaneSpeed(Lane::TextureType laneTextureType) const;

   private:
    static std::map<Lane::TextureType, std::vector<Lane::TextureType>>
        mNextLaneTypes;
    static std::map<Lane::TextureType, bool> mIsStaticLane;

    enum Layer { LaneLayer, TrafficLightLayer, LayerCount };

    SceneNode* mLevelNode;
    std::array<SceneNode*, LayerCount> mLevelLayers;

    float mObstacleSpeed;

    int mMinSpawnRate;
    int mMaxSpawnRate;

    float mSpeedScale;
};
