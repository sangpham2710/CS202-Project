#pragma once

#include <SFML/Graphics/Texture.hpp>

#include "MusicPlayer.hpp"
#include "ResourceHolder.hpp"
#include "ResourceIdentifiers.hpp"
#include "SoundPlayer.hpp"

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
    void setSoundPlayer(SoundPlayer* soundPlayer);
    void setMusicPlayer(MusicPlayer* musicPlayer);

    SettingsSingleton(SettingsSingleton const&) = delete;
    void operator=(SettingsSingleton const&) = delete;

   private:
    SettingsSingleton();

    int mCharacterType;
    int mCurrentLevelNumber;
    float mMusicVolume;
    float mSoundVolume;
    SoundPlayer* mSoundPlayer;
    MusicPlayer* mMusicPlayer;
};
