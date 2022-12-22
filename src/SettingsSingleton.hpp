#pragma once

#include <SFML/Graphics/Texture.hpp>

#include "ResourceHolder.hpp"
#include "ResourceIdentifiers.hpp"

class SettingsSingleton {
   public:
    static SettingsSingleton& getInstance();
    void setCharacterType(int type);
    int getCharacterType();
    void setCurrentLevelNumber(int level);
    int getCurrentLevelNumber();
    void setMusicVolume(float volume);
    float getMusicVolume();
    void setSoundVolume(float volume);
    float getSoundVolume();

    SettingsSingleton(SettingsSingleton const&) = delete;
    void operator=(SettingsSingleton const&) = delete;

   private:
    SettingsSingleton();

    int mCharacterType;
    int mCurrentLevelNumber;
    float mMusicVolume;
    float mSoundVolume;
};
