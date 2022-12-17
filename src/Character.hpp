#pragma once

#include <SFML/Graphics/Sprite.hpp>

#include "Animation.hpp"
#include "DataTables.hpp"
#include "Entity.hpp"
#include "ResourceIdentifiers.hpp"

class Character : public Entity {
   public:
    enum class Direction {
        CharacterUp,
        CharacterDown,
        CharacterLeft,
        CharacterRight,
        TypeCount
    };

   public:
    Character(int type);
    virtual unsigned int getCategory() const override;
    virtual sf::FloatRect getBoundingRect() const override;
    virtual bool isMarkedForRemoval() const override;
    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();
    bool isMoving() const;
    void setTextureWrecked();
    void setExplosionPosition(sf::Vector2f position);

   private:
    virtual void drawCurrent(sf::RenderTarget& target,
                             sf::RenderStates states) const override;
    virtual void updateCurrent(sf::Time dt, CommandQueue& commands) override;

    sf::Sprite mSprite;
    Animation mAnimation;
    Animation mExplosion;
    bool mIsMoving;
    bool mShowExplosion;

    int mType;
};
