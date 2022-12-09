#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "ResourceHolder.hpp"
#include "ResourceIdentifiers.hpp"

class TexturesSingleton {
   public:
    static TexturesSingleton& getInstance();

    TexturesSingleton(TexturesSingleton const&) = delete;
    void operator=(TexturesSingleton const&) = delete;

    TextureHolder& getTextures();

   private:
    TexturesSingleton();

    TextureHolder mTextures;
};