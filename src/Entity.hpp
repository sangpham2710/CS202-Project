#pragma once

#include "SceneNode.hpp"


class Entity : public SceneNode {
   public:
    explicit Entity();

    void setVelocity(sf::Vector2f velocity);
    void setVelocity(float vx, float vy);
    void accelerate(sf::Vector2f velocity);
    void accelerate(float vx, float vy);
    sf::Vector2f getVelocity() const;

    virtual bool isDestroyed() const override;
    void destroy();

   protected:
    virtual void updateCurrent(sf::Time dt, CommandQueue& commands) override;

   private:
    sf::Vector2f mVelocity;
    bool mIsDestroyed;
};
