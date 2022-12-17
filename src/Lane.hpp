#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include <vector>

#include "Entity.hpp"
#include "Obstacle.hpp"
#include "ResourceIdentifiers.hpp"
#include "TrafficLight.hpp"
#include "World.hpp"

class Lane : public Entity {
   public:
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
         TrafficLight* trafficLight = nullptr);

   private:
    virtual void drawCurrent(sf::RenderTarget& target,
                             sf::RenderStates states) const override;
    virtual void updateCurrent(sf::Time dt, CommandQueue& commands) override;
    virtual unsigned int getCategory() const override;

    void generateObstacle(sf::Time dt);
    void updateSpeed();
    void generateMovingObstacles(sf::Time dt);
    void generateStandingObstacles();
    Obstacle::Type getRandomObstacleType() const;

    Type mType;
    TextureType mTextureType;
    bool mHasObstacles;
    Direction mDirection;
    float mSpeed;
    float maxSpeed;
    sf::Sprite mSprite;
    TrafficLight* mTrafficLight;
    static std::map<Lane::TextureType, std::vector<Obstacle::Type>>
        allowedObstacleTypes;
};