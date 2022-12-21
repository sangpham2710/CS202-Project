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
             Lane::TextureType::LilyPadBelow,
             Lane::TextureType::LilyPadSingle,
             Lane::TextureType::PavementBelow,
             Lane::TextureType::Railway,
             Lane::TextureType::RoadBelow,
             Lane::TextureType::RoadSingle,
         }},
        {Lane::TextureType::LilyPadAbove,
         {
             Lane::TextureType::PavementBelow,
             Lane::TextureType::Railway,
             Lane::TextureType::RoadBelow,
             Lane::TextureType::RoadSingle,
         }},
        {Lane::TextureType::LilyPadBelow,
         {
             Lane::TextureType::LilyPadAbove,
         }},
        {Lane::TextureType::LilyPadSingle,
         {
             Lane::TextureType::PavementBelow,
             Lane::TextureType::Railway,
             Lane::TextureType::RoadBelow,
             Lane::TextureType::RoadSingle,
         }},
        {Lane::TextureType::PavementAbove,
         {
             Lane::TextureType::LilyPadBelow,
             Lane::TextureType::LilyPadSingle,
             Lane::TextureType::Railway,
             Lane::TextureType::RoadBelow,
             Lane::TextureType::RoadSingle,
         }},
        {Lane::TextureType::PavementBelow,
         {
             Lane::TextureType::PavementAbove,
         }},
        {Lane::TextureType::Railway,
         {
             Lane::TextureType::LilyPadBelow,
             Lane::TextureType::LilyPadSingle,
             Lane::TextureType::PavementBelow,
             Lane::TextureType::Railway,
             Lane::TextureType::RoadBelow,
             Lane::TextureType::RoadSingle,
         }},
        {Lane::TextureType::RoadAbove,
         {
             Lane::TextureType::LilyPadBelow,
             Lane::TextureType::LilyPadSingle,
             Lane::TextureType::PavementBelow,
             Lane::TextureType::Railway,
         }},
        {Lane::TextureType::RoadBelow,
         {
             Lane::TextureType::RoadAbove,
             Lane::TextureType::RoadMiddle,

         }},
        {Lane::TextureType::RoadMiddle,
         {
             Lane::TextureType::RoadAbove,
             Lane::TextureType::RoadMiddle,
         }},
        {Lane::TextureType::RoadSingle,
         {
             Lane::TextureType::LilyPadBelow,
             Lane::TextureType::LilyPadSingle,
             Lane::TextureType::PavementBelow,
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
      mObstacleSpeed(100.f),
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
        float laneSpeed = getLaneSpeed(laneTextureType);
        int laneSpawnRate =
            mMinSpawnRate + randomInt(mMaxSpawnRate - mMinSpawnRate + 1);
        int lanePositionY = (11 - laneID) * Constants::BLOCK_SIZE;

        if (mIsStaticLane[currentType]) {
            // create static lane
            std::unique_ptr<Lane> lane(new Lane(laneType, laneTextureType,
                                                hasObstacle, laneDirection,
                                                laneSpeed, laneSpawnRate));
            lane->setPosition(0, lanePositionY);
            mLevelLayers[LaneLayer]->attachChild(std::move(lane));

        } else {
            // create dynamic lane

            if (randomInt(100) < 70) {
                std::unique_ptr<TrafficLight> trafficLight(new TrafficLight());
                trafficLight->setPosition(0, lanePositionY);
                std::unique_ptr<Lane> lane(new Lane(
                    laneType, laneTextureType, hasObstacle, laneDirection,
                    laneSpeed, laneSpawnRate, trafficLight.get()));
                lane->setPosition(0, lanePositionY);

                mLevelLayers[LaneLayer]->attachChild(std::move(lane));
                mLevelLayers[TrafficLightLayer]->attachChild(
                    std::move(trafficLight));

            } else {
                std::unique_ptr<Lane> lane(new Lane(laneType, laneTextureType,
                                                    hasObstacle, laneDirection,
                                                    laneSpeed, laneSpawnRate));
                lane->setPosition(0, lanePositionY);
                
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

    saveLevel("test.txt");
}

void LevelManager::prepareLevel(int levelNumber) {
    mObstacleSpeed = calcLevelObstacleSpeed(levelNumber);
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
    std::ofstream fout(filename);
    for (int laneID = 0;laneID < 12;++laneID) {
        Lane* lane = dynamic_cast<Lane*>(mLevelLayers[LaneLayer]->getChildren()[laneID]);
        if (lane) {
            //Lane Type
            fout << int(lane->getLaneType()) << "\n";
            //Lane Texture Type
            fout << int(lane->getTextureType()) << "\n";
            //has Obstacle
            fout << int(lane->hasObstacles()) << "\n";
            //Direction
            fout << int(lane->getDirection()) << "\n";
            //mSpeed
            fout << float(lane->getSpeed()) << "\n";
            //mSpawnRate
            fout << int(lane->getSpawnRate()) << "\n";
            //has Traffic Light
            fout << int(lane->hasTrafficLight()) << "\n";
        }
    } 
    fout.close();
}

void LevelManager::loadLevel(const std::string& filename) {
    std::ifstream fin(filename);
    int iLaneType, iTextureType, iHasObstacles, iDirection, iSpawnRate, iHasTrafficLight;
    float fSpeed;
    for (int laneID = 0; laneID < 12; ++laneID) {
        fin >> iLaneType >> iTextureType >> iHasObstacles >> iDirection >> fSpeed >> iSpawnRate >> iHasTrafficLight;
        Lane::Type laneType = Lane::Type(iLaneType);
        Lane::TextureType laneTextureType = Lane::TextureType(iTextureType);
        Lane::Direction laneDirection = Lane::Direction(iDirection);
        int lanePositionY = (11 - laneID) * Constants::BLOCK_SIZE;

        if (iLaneType==0) {
            // create static lane
            std::unique_ptr<Lane> lane(new Lane(laneType, laneTextureType,
                iHasObstacles, laneDirection,
                fSpeed, iSpawnRate));
            lane->setPosition(0, lanePositionY);
            mLevelLayers[LaneLayer]->attachChild(std::move(lane));
        }
        else {
            // create dynamic lane
            if (iHasTrafficLight) {//has Traffic Light
                std::unique_ptr<TrafficLight> trafficLight(new TrafficLight());
                trafficLight->setPosition(0, lanePositionY);
                std::unique_ptr<Lane> lane(new Lane(
                    laneType, laneTextureType, iHasObstacles, laneDirection,
                    fSpeed, iSpawnRate, trafficLight.get()));
                lane->setPosition(0, lanePositionY);

                mLevelLayers[LaneLayer]->attachChild(std::move(lane));
                mLevelLayers[TrafficLightLayer]->attachChild(
                    std::move(trafficLight));

            }
            else {
                std::unique_ptr<Lane> lane(new Lane(laneType, laneTextureType,
                    iHasObstacles, laneDirection,
                    fSpeed, iSpawnRate));
                lane->setPosition(0, lanePositionY);

                mLevelLayers[LaneLayer]->attachChild(std::move(lane));

            }
    }
    fin.close();
}

float LevelManager::calcLevelObstacleSpeed(int levelNumber) const {
    return mObstacleSpeed + (levelNumber * mSpeedScale);
}

float LevelManager::getLaneSpeed(Lane::TextureType laneTextureType) const {
    switch (laneTextureType) {
        case Lane::TextureType::Railway:
            return mObstacleSpeed * 8.0f;
        case Lane::TextureType::RoadAbove:
            return mObstacleSpeed * randomFloat(1.0f, 1.5f);
        case Lane::TextureType::RoadBelow:
            return mObstacleSpeed * randomFloat(1.0f, 1.5f);
        case Lane::TextureType::RoadMiddle:
            return mObstacleSpeed * randomFloat(1.0f, 1.5f);
        case Lane::TextureType::RoadSingle:
            return mObstacleSpeed * randomFloat(1.0f, 1.5f);
        default:
            return mObstacleSpeed;
    }
}

int LevelManager::calcLevelMinObstacleSpawnRate(int levelNumber) const {
    return mMinSpawnRate + (levelNumber * 5);
}

int LevelManager::calcLevelMaxObstacleSpawnRate(int levelNumber) const {
    return mMaxSpawnRate + (levelNumber * 5);
}
