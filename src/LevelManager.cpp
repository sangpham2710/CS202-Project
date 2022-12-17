#include "LevelManager.hpp"

#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>

#include "Constants.hpp"
#include "TexturesSingleton.hpp"
#include "TrafficLight.hpp"
#include "Utility.hpp"

std::map<Lane::TextureType, std::vector<Lane::TextureType>>
    LevelManager::mNextLaneTypes = {
        {Lane::TextureType::Grass,
         {
             Lane::TextureType::LilyPadAbove,
             Lane::TextureType::LilyPadSingle,
             Lane::TextureType::PavementAbove,
             Lane::TextureType::Railway,
             Lane::TextureType::RoadAbove,
             Lane::TextureType::RoadSingle,
         }},
        {Lane::TextureType::LilyPadAbove,
         {
             Lane::TextureType::LilyPadBelow,
         }},
        {Lane::TextureType::LilyPadBelow,
         {
             Lane::TextureType::PavementAbove,
             Lane::TextureType::Railway,
             Lane::TextureType::RoadAbove,
             Lane::TextureType::RoadSingle,
         }},
        {Lane::TextureType::LilyPadSingle,
         {
             Lane::TextureType::PavementAbove,
             Lane::TextureType::Railway,
             Lane::TextureType::RoadAbove,
             Lane::TextureType::RoadSingle,
         }},
        {Lane::TextureType::PavementAbove,
         {
             Lane::TextureType::PavementBelow,
         }},
        {Lane::TextureType::PavementBelow,
         {
             Lane::TextureType::LilyPadAbove,
             Lane::TextureType::LilyPadSingle,
             Lane::TextureType::Railway,
             Lane::TextureType::RoadAbove,
             Lane::TextureType::RoadSingle,
         }},
        {Lane::TextureType::Railway,
         {
             Lane::TextureType::LilyPadAbove,
             Lane::TextureType::LilyPadSingle,
             Lane::TextureType::PavementAbove,
             Lane::TextureType::Railway,
             Lane::TextureType::RoadAbove,
             Lane::TextureType::RoadSingle,
         }},
        {Lane::TextureType::RoadAbove,
         {
             Lane::TextureType::RoadBelow,
             Lane::TextureType::RoadMiddle,
         }},
        {Lane::TextureType::RoadBelow,
         {
             Lane::TextureType::LilyPadAbove,
             Lane::TextureType::LilyPadSingle,
             Lane::TextureType::PavementAbove,
             Lane::TextureType::Railway,
             Lane::TextureType::RoadAbove,
             Lane::TextureType::RoadSingle,
         }},
        {Lane::TextureType::RoadMiddle,
         {
             Lane::TextureType::RoadBelow,
             Lane::TextureType::RoadMiddle,
         }},
        {Lane::TextureType::RoadSingle,
         {
             Lane::TextureType::LilyPadAbove,
             Lane::TextureType::LilyPadSingle,
             Lane::TextureType::PavementAbove,
             Lane::TextureType::Railway,
         }},
};

std::map<Lane::TextureType, bool> LevelManager::mIsStaticLane = {
    {Lane::TextureType::Grass, true},
    {Lane::TextureType::LilyPadAbove, true},
    {Lane::TextureType::LilyPadBelow, true},
    {Lane::TextureType::LilyPadSingle, true},
    {Lane::TextureType::PavementAbove, true},
    {Lane::TextureType::PavementBelow, true},
    {Lane::TextureType::Railway, false},
    {Lane::TextureType::RoadAbove, false},
    {Lane::TextureType::RoadBelow, false},
    {Lane::TextureType::RoadMiddle, false},
    {Lane::TextureType::RoadSingle, false},
};

LevelManager::LevelManager() : LevelManager(nullptr) {
}

LevelManager::LevelManager(SceneNode* levelNode)
    : mLevelNode(levelNode),
      mMinObstacleSpeed(50.0f),
      mMaxObstacleSpeed(150.f),
      mMinSpawnRate(10),
      mMaxSpawnRate(30),
      mSpeedScale(0.1f) {
}

void LevelManager::setLevelNode(SceneNode* levelNode) {
    mLevelNode = levelNode;
}

void LevelManager::generateLevel(int levelNumber) {
    prepareLevel(levelNumber);
    Lane::TextureType currentType = Lane::TextureType::Grass;
    for (int laneID = 0; laneID < 12; ++laneID) {
        Lane::Type laneType = mIsStaticLane[currentType] ? Lane::Type::Static
                                                         : Lane::Type::Dynamic;

        Lane::TextureType laneTextureType = currentType;
        bool hasObstacle = laneID == 0 ? false : randomInt(100) < 90;

        Lane::Direction laneDirection =
            randomInt(2) == 0 ? Lane::Direction::Left : Lane::Direction::Right;
        float laneSpeed = randomFloat(mMinObstacleSpeed, mMaxObstacleSpeed);
        int laneSpawnRate =
            mMinSpawnRate + randomInt(mMaxSpawnRate - mMinSpawnRate + 1);

        if (mIsStaticLane[currentType]) {
            // create static lane
            std::unique_ptr<Lane> lane(new Lane(laneType, laneTextureType,
                                                hasObstacle, laneDirection,
                                                laneSpeed, laneSpawnRate));
            lane->setPosition(0, laneID * Constants::BLOCK_SIZE);
            mLevelLayers[LaneLayer]->attachChild(std::move(lane));

        } else {
            // create dynamic lane

            if (randomInt(100) < 70) {
                std::unique_ptr<TrafficLight> trafficLight(new TrafficLight());
                trafficLight->setPosition(0, laneID * Constants::BLOCK_SIZE);
                std::unique_ptr<Lane> lane(new Lane(
                    laneType, laneTextureType, hasObstacle, laneDirection,
                    laneSpeed, laneSpawnRate, trafficLight.get()));
                lane->setPosition(0, laneID * Constants::BLOCK_SIZE);

                mLevelLayers[LaneLayer]->attachChild(std::move(lane));
                mLevelLayers[TrafficLightLayer]->attachChild(
                    std::move(trafficLight));

            } else {
                std::unique_ptr<Lane> lane(new Lane(laneType, laneTextureType,
                                                    hasObstacle, laneDirection,
                                                    laneSpeed, laneSpawnRate));
                lane->setPosition(0, laneID * Constants::BLOCK_SIZE);

                mLevelLayers[LaneLayer]->attachChild(std::move(lane));
            }
        }

        // select next lane type
        auto nextTypes = mNextLaneTypes.find(currentType);
        if (nextTypes != mNextLaneTypes.end()) {
            currentType =
                nextTypes->second[randomInt(nextTypes->second.size())];
        }
    }
}

void LevelManager::prepareLevel(int levelNumber) {
    mMinObstacleSpeed = calcLevelMinObstacleSpeed(levelNumber);
    mMaxObstacleSpeed = calcLevelMaxObstacleSpeed(levelNumber);
    mMinSpawnRate = calcLevelMinObstacleSpawnRate(levelNumber);
    mMaxSpawnRate = calcLevelMaxObstacleSpawnRate(levelNumber);

    // clear all layers
    while (!mLevelNode->getChildren().empty()) {
        mLevelNode->detachChild(*mLevelNode->getChildren().front());
    }

    // create layers
    for (std::size_t i = 0; i < LayerCount; ++i) {
        SceneNode::Ptr layer(new SceneNode());
        mLevelLayers[i] = layer.get();
        mLevelNode->attachChild(std::move(layer));
    }
}

void LevelManager::saveLevel(const std::string& filename) const {
}

void LevelManager::loadLevel(const std::string& filename) {
}

float LevelManager::calcLevelMinObstacleSpeed(int levelNumber) const {
    return mMinObstacleSpeed + (levelNumber * mSpeedScale);
}

float LevelManager::calcLevelMaxObstacleSpeed(int levelNumber) const {
    return mMaxObstacleSpeed + (levelNumber * mSpeedScale);
}

int LevelManager::calcLevelMinObstacleSpawnRate(int levelNumber) const {
    return mMinSpawnRate + (levelNumber * 2);
}

int LevelManager::calcLevelMaxObstacleSpawnRate(int levelNumber) const {
    return mMaxSpawnRate + (levelNumber * 2);
}
