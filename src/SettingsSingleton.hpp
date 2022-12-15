#pragma once

#include <SFML/Graphics/Texture.hpp>

#include "ResourceHolder.hpp"
#include "ResourceIdentifiers.hpp"

class SettingsSingleton {
public:
    static SettingsSingleton& getInstance();
    void setCharacterType(int type);
    int getCharacterType();

    SettingsSingleton(SettingsSingleton const&) = delete;
    void operator=(SettingsSingleton const&) = delete;

    TextureHolder& getTextures();

private:
    SettingsSingleton();

    TextureHolder mTextures;
    int characterType = 0;
};
