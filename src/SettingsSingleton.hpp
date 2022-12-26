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
    int getCharacterType() const;
    void setCurrentLevelNumber(int level);
    int getCurrentLevelNumber() const;
    void setMusicVolume(float volume);
    float getMusicVolume() const;
    void setSoundVolume(float volume);
    float getSoundVolume() const;
    void setSoundPlayer(SoundPlayer* soundPlayer);
    void setMusicPlayer(MusicPlayer* musicPlayer);
    void setIsLevelLoaded(bool isLoaded);
    bool getIsLevelLoaded() const;
    void setLoadingLevelFilename(const std::string& filename);
    std::string getLoadingLevelFilename() const;

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
    bool mIsLevelLoaded;
    std::string mLoadingLevelFilename;
};
