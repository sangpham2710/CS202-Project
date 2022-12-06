#pragma once

#include <SFML/Graphics/Sprite.hpp>

#include "Entity.hpp"
#include "ResourceIdentifiers.hpp"

class Character : public Entity {
   public:
    Character(const TextureHolder& textures);
    virtual unsigned int getCategory() const;
    virtual sf::FloatRect getBoundingRect() const;
    virtual bool isMarkedForRemoval() const;

   private:
    virtual void drawCurrent(sf::RenderTarget& target,
                             sf::RenderStates states) const;
    virtual void updateCurrent(sf::Time dt, CommandQueue& commands);

    sf::Sprite mSprite;
    bool mIsMarkedForRemoval;
};