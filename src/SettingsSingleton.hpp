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

   private:
    SettingsSingleton();

    int characterType = 0;
};
