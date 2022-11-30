#pragma once

#include <SFML/Graphics/Sprite.hpp>

#include "SceneNode.hpp"


class SpriteNode : public SceneNode {
   public:
    explicit SpriteNode(const sf::Texture& texture);
    SpriteNode(const sf::Texture& texture, const sf::IntRect& textureRect);

   private:
    virtual void drawCurrent(sf::RenderTarget& target,
                             sf::RenderStates states) const;

   private:
    sf::Sprite mSprite;
};
