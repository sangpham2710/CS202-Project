#include "Lane.hpp"

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <algorithm>
#include <numeric>
#include <random>

#include "CommandQueue.hpp"
#include "Constants.hpp"
#include "DataTables.hpp"
#include "ResourceHolder.hpp"
#include "TexturesSingleton.hpp"
#include "Utility.hpp"

namespace {
const std::vector<LaneData> Table = initializeLaneData();
}  // namespace

std::map<Lane::TextureType, std::vector<Obstacle::Type>>
    Lane::allowedObstacleTypes = {
        {Lane::TextureType::Railway,
         {
             Obstacle::Type::BlueBus,
             Obstacle::Type::OrangeBus,
         }},
        {Lane::TextureType::RoadAbove,
         {
             Obstacle::Type::BlueCar,
             Obstacle::Type::GrayCar,
             Obstacle::Type::NewVan,
             Obstacle::Type::OldVan,
             Obstacle::Type::PoliceCar,
             Obstacle::Type::RedCar,
             Obstacle::Type::RedStripedCar,
             Obstacle::Type::RedTruck,
             Obstacle::Type::SchoolBus,
             Obstacle::Type::WhiteTruck,
             Obstacle::Type::YellowCab,
             Obstacle::Type::YellowCar,
         }},
        {Lane::TextureType::RoadMiddle,
         {
             Obstacle::Type::BlueCar,
             Obstacle::Type::GrayCar,
             Obstacle::Type::NewVan,
             Obstacle::Type::OldVan,
             Obstacle::Type::PoliceCar,
             Obstacle::Type::RedCar,
             Obstacle::Type::RedStripedCar,
             Obstacle::Type::RedTruck,
             Obstacle::Type::SchoolBus,
             Obstacle::Type::WhiteTruck,
             Obstacle::Type::YellowCab,
             Obstacle::Type::YellowCar,
         }},
        {Lane::TextureType::RoadBelow,
         {
             Obstacle::Type::BlueCar,
             Obstacle::Type::GrayCar,
             Obstacle::Type::NewVan,
             Obstacle::Type::OldVan,
             Obstacle::Type::PoliceCar,
             Obstacle::Type::RedCar,
             Obstacle::Type::RedStripedCar,
             Obstacle::Type::RedTruck,
             Obstacle::Type::SchoolBus,
             Obstacle::Type::WhiteTruck,
             Obstacle::Type::YellowCab,
             Obstacle::Type::YellowCar,
         }},
        {Lane::TextureType::RoadSingle,
         {
             Obstacle::Type::BlueCar,
             Obstacle::Type::GrayCar,
             Obstacle::Type::NewVan,
             Obstacle::Type::OldVan,
             Obstacle::Type::PoliceCar,
             Obstacle::Type::RedCar,
             Obstacle::Type::RedStripedCar,
             Obstacle::Type::RedTruck,
             Obstacle::Type::SchoolBus,
             Obstacle::Type::WhiteTruck,
             Obstacle::Type::YellowCab,
             Obstacle::Type::YellowCar,
         }},
        {Lane::TextureType::PavementAbove,
         {
             Obstacle::Type::FireHydrant,
         }},
        {Lane::TextureType::PavementBelow,
         {
             Obstacle::Type::FireHydrant,
         }},
        {Lane::TextureType::Grass,
         {
             Obstacle::Type::Bush,
         }},
        {Lane::TextureType::LilyPadSingle,
         {
             Obstacle::Type::WaterSingle,
         }},
        {Lane::TextureType::LilyPadAbove,
         {
             Obstacle::Type::WaterAbove,
         }},
        {Lane::TextureType::LilyPadBelow,
         {
             Obstacle::Type::WaterBelow,
         }},
};

Lane::Lane(Lane::Type type, Lane::TextureType textureType, bool hasObstacles,
           Lane::Direction direction, float speed, int spawnRate,
           TrafficLight* trafficLight)
    : mType(type),
      mTextureType(textureType),
      mHasObstacles(hasObstacles),
      mDirection(direction),
      mSpeed(speed),
      mTrafficLight(trafficLight),
      maxSpeed(speed),
      mObstacleSpawnRate(spawnRate) {
    mSprite = sf::Sprite(TexturesSingleton::getInstance().getTextures().get(
        Table[(unsigned)textureType].texture));
    if (mHasObstacles && mType == Type::Static) generateStandingObstacles();
    if (mHasObstacles && mType == Type::Dynamic && mTrafficLight) updateSpeed();
}

void Lane::drawCurrent(sf::RenderTarget& target,
                       sf::RenderStates states) const {
    int numsOfBlocks = Constants::SCREEN_WIDTH / Constants::BLOCK_SIZE;

    for (int i = 0; i < numsOfBlocks; i++) {
        sf::Sprite laneSprite = mSprite;
        laneSprite.setPosition(i * Constants::BLOCK_SIZE, 0);
        target.draw(laneSprite, states);
    }
}

void Lane::updateCurrent(sf::Time dt, CommandQueue& commands) {
    if (!mHasObstacles) return;
    // Generate new obstacles
    if (mType == Type::Dynamic) generateMovingObstacles(dt);
    if (mType == Type::Dynamic && mTrafficLight) updateSpeed();
}

void Lane::updateSpeed() {
    if (mTrafficLight->getState() == TrafficLight::State::Red) {
        mSpeed = 0;
    } else if (mTrafficLight->getState() == TrafficLight::State::Yellow) {
        mSpeed = maxSpeed / 2;
    } else if (mTrafficLight->getState() == TrafficLight::State::Green) {
        mSpeed = maxSpeed;
    }

    auto children = getChildren();
    for (SceneNode* each : children) {
        Obstacle* obstacle = dynamic_cast<Obstacle*>(each);
        if (obstacle != nullptr) {
            obstacle->setVelocity(mDirection * mSpeed, 0.f);
        }
    }
}

unsigned int Lane::getCategory() const {
    return Category::Lane;
}

void Lane::generateMovingObstacles(sf::Time dt) {
    int tmp = randomInt(10000);
    if (tmp >= mObstacleSpawnRate) return;

    Obstacle::Type obstacleType = getRandomObstacleType();

    auto children = this->getChildren();
    auto lastObstacle = children.empty() ? nullptr : children.back();
    if (mDirection == Lane::Left) {
        std::unique_ptr<Obstacle> obstacle(
            new Obstacle(obstacleType, Obstacle::Direction::Left));

        if (lastObstacle) {
            float end = lastObstacle->getPosition().x +
                        lastObstacle->getBoundingRect().width;

            if (end > Constants::SCREEN_WIDTH) return;
        }

        obstacle->setPosition(Constants::SCREEN_WIDTH, mSprite.getPosition().y);
        obstacle->setVelocity(mDirection * mSpeed, 0.f);
        attachChild(std::move(obstacle));
    }
    if (mDirection == Lane::Right) {
        std::unique_ptr<Obstacle> obstacle(
            new Obstacle(obstacleType, Obstacle::Direction::Right));

        if (lastObstacle) {
            float start = lastObstacle->getPosition().x;
            if (start < 0) return;
        }

        obstacle->setPosition(-obstacle->getBoundingRect().width,
                              mSprite.getPosition().y);
        obstacle->setVelocity(mDirection * mSpeed, 0.f);

        attachChild(std::move(obstacle));
    }
}

void Lane::generateStandingObstacles() {
    std::vector<int> blocks(Constants::SCREEN_WIDTH / Constants::BLOCK_SIZE);
    std::iota(blocks.begin(), blocks.end(), 0);
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(blocks.begin(), blocks.end(), g);
    auto numObstacles = mTextureType == TextureType::LilyPadAbove ||
                                mTextureType == TextureType::LilyPadBelow ||
                                mTextureType == TextureType::LilyPadSingle
                            ? randomInt(8) + 1
                        : mTextureType == TextureType::PavementAbove ||
                                mTextureType == TextureType::PavementBelow
                            ? randomInt(2) + 1
                            : randomInt(3) + 1;
    blocks.resize(numObstacles);

    mSpeed = 0.0;
    for (auto& x : blocks) {
        std::unique_ptr<Obstacle> obstacle(
            new Obstacle(getRandomObstacleType(), Obstacle::Direction::Left));
        obstacle->setPosition(x * Constants::BLOCK_SIZE,
                              mSprite.getPosition().y);
        obstacle->setVelocity(0.0f, 0.0f);
        attachChild(std::move(obstacle));
    }
}

Obstacle::Type Lane::getRandomObstacleType() const {
    int index = randomInt(allowedObstacleTypes[mTextureType].size());
    return allowedObstacleTypes[mTextureType][index];
}
