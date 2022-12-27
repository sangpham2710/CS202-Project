#include "LevelManager.hpp"

#include <fstream>
#include <memory>
#include <sstream>

#include "Constants.hpp"
#include "SettingsSingleton.hpp"
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
             Lane::TextureType::Grass,
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
             Lane::TextureType::Grass,
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
             Lane::TextureType::Grass,
         }},
        {Lane::TextureType::Railway,
         {
             Lane::TextureType::LilyPadBelow,
             Lane::TextureType::LilyPadSingle,
             Lane::TextureType::PavementBelow,
             Lane::TextureType::Railway,
             Lane::TextureType::RoadBelow,
             Lane::TextureType::RoadSingle,
             Lane::TextureType::Grass,
         }},
        {Lane::TextureType::RoadAbove,
         {
             Lane::TextureType::LilyPadBelow,
             Lane::TextureType::LilyPadSingle,
             Lane::TextureType::PavementBelow,
             Lane::TextureType::Railway,
             Lane::TextureType::Grass,
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
      mMinSpawnRate(30),    // old is 30
      mMaxSpawnRate(50),    // and 50
      mSpeedScale(10.0f) {  // old os 10.0
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
    std::ofstream ofs(filename);
    if (!ofs) {
        throw std::runtime_error("Could not open file " + filename);
    }

    ofs << SettingsSingleton::getInstance().getCurrentLevelNumber() << '\n';
    for (auto& child : mLevelLayers[LaneLayer]->getChildren()) {
        if (child->getCategory() == Category::Lane) {
            Lane* lane = static_cast<Lane*>(child);
            // Save all fields of lane
            ofs << static_cast<int>(lane->mType) << ' '
                << static_cast<int>(lane->mTextureType) << ' '
                << static_cast<int>(lane->mHasObstacles) << ' '
                << static_cast<int>(lane->mDirection) << ' ' << lane->mSpeed
                << ' ' << lane->mObstacleSpawnRate << ' '
                << (lane->mTrafficLight != nullptr) << '\n';
        }
    }

    ofs.close();
}

void LevelManager::loadLevel(const std::string& filename) {
    std::ifstream ifs(filename);
    if (!ifs) {
        throw std::runtime_error("Could not open file " + filename);
    }

    int levelNumber;
    ifs >> levelNumber;
    SettingsSingleton::getInstance().setCurrentLevelNumber(levelNumber);
    prepareLevel(levelNumber);

    while (!ifs.eof()) {
        int laneType, laneTextureType, hasObstacle, laneDirection;
        float laneSpeed;
        int laneSpawnRate;
        bool hasTrafficLight;

        ifs >> laneType >> laneTextureType >> hasObstacle >> laneDirection >>
            laneSpeed >> laneSpawnRate >> hasTrafficLight;

        if (ifs.eof()) {
            break;
        }

        int lanePositionY =
            (11 - mLevelLayers[LaneLayer]->getChildren().size()) *
            Constants::BLOCK_SIZE;

        if (laneType == static_cast<int>(Lane::Type::Static)) {
            // create static lane
            std::unique_ptr<Lane> lane(new Lane(
                static_cast<Lane::Type>(laneType),
                static_cast<Lane::TextureType>(laneTextureType), hasObstacle,
                static_cast<Lane::Direction>(laneDirection), laneSpeed,
                laneSpawnRate));
            lane->setPosition(0, lanePositionY);
            mLevelLayers[LaneLayer]->attachChild(std::move(lane));

        } else {
            // create dynamic lane
            if (hasTrafficLight) {
                std::unique_ptr<TrafficLight> trafficLight(new TrafficLight());
                trafficLight->setPosition(0, lanePositionY);
                std::unique_ptr<Lane> lane(new Lane(
                    static_cast<Lane::Type>(laneType),
                    static_cast<Lane::TextureType>(laneTextureType),
                    hasObstacle, static_cast<Lane::Direction>(laneDirection),
                    laneSpeed, laneSpawnRate, trafficLight.get()));
                lane->setPosition(0, lanePositionY);

                mLevelLayers[LaneLayer]->attachChild(std::move(lane));
                mLevelLayers[TrafficLightLayer]->attachChild(
                    std::move(trafficLight));

            } else {
                std::unique_ptr<Lane> lane(new Lane(
                    static_cast<Lane::Type>(laneType),
                    static_cast<Lane::TextureType>(laneTextureType),
                    hasObstacle, static_cast<Lane::Direction>(laneDirection),
                    laneSpeed, laneSpawnRate));
                lane->setPosition(0, lanePositionY);

                mLevelLayers[LaneLayer]->attachChild(std::move(lane));
            }
        }
    }

    ifs.close();
}

float LevelManager::calcLevelObstacleSpeed(int levelNumber) const {
    return mObstacleSpeed + (levelNumber * levelNumber * mSpeedScale);
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
    return mMinSpawnRate + (levelNumber * levelNumber * 10);
}

int LevelManager::calcLevelMaxObstacleSpawnRate(int levelNumber) const {
    return mMaxSpawnRate + (levelNumber * levelNumber * 10);
}
