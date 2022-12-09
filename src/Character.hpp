#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include "Animation.hpp"

#include "Entity.hpp"
#include "ResourceIdentifiers.hpp"

class Character : public Entity {
   public:
    Character();
    virtual unsigned int getCategory() const override;
    virtual sf::FloatRect getBoundingRect() const override;
    virtual bool isMarkedForRemoval() const override;
    void moveUpAnimation();
    void moveDownAnimation();
    void moveLeftAnimation();
    void moveRightAnimation();
    void drawCurrent(sf::RenderTarget& target, sf::RenderStates states);
   private:
    virtual void drawCurrent(sf::RenderTarget& target,
                             sf::RenderStates states) const override;
    virtual void updateCurrent(sf::Time dt, CommandQueue& commands) override;

    sf::Sprite mSprite;
    Animation mAnimation;
    bool mIsMarkedForRemoval;
};
