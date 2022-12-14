#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include <map>
#include <vector>

#include "Entity.hpp"
#include "Obstacle.hpp"
#include "ResourceIdentifiers.hpp"
#include "TrafficLight.hpp"

class Lane : public Entity {
   public:
    friend class LevelManager;
    enum class Type { Static, Dynamic };
    // TextureType
    enum class TextureType {
        Grass,
        LilyPadAbove,
        LilyPadBelow,
        LilyPadSingle,
        PavementAbove,
        PavementBelow,
        Railway,
        RoadAbove,
        RoadBelow,
        RoadMiddle,
        RoadSingle,
        TypeCount
    };

    // Direction of obstacles
    enum Direction {
        Left = -1,
        NoDirection = 0,
        Right = 1,
    };

    Lane(Type type, TextureType textureType, bool hasObstacles = true,
         Direction direction = NoDirection, float speed = 0.0f,
         int spawnRate = 0, TrafficLight* trafficLight = nullptr);

   private:
    virtual void drawCurrent(sf::RenderTarget& target,
                             sf::RenderStates states) const override;
    virtual void updateCurrent(sf::Time dt, CommandQueue& commands) override;
    virtual unsigned int getCategory() const override;

    void updateSpeed();
    void generateMovingObstacles(sf::Time dt);
    void generateStandingObstacles();
    Obstacle::Type getRandomObstacleType() const;

    static std::map<Lane::TextureType, std::vector<Obstacle::Type>>
        allowedObstacleTypes;

    sf::Sprite mSprite;
    float mSpeed;

    Type mType;
    TextureType mTextureType;
    bool mHasObstacles;
    Direction mDirection;
    float maxSpeed;
    int mObstacleSpawnRate;
    TrafficLight* mTrafficLight;
};