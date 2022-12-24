#include "SettingsSingleton.hpp"

SettingsSingleton::SettingsSingleton()
    : mCharacterType(0),
      mCurrentLevelNumber(1),
      mMusicVolume(10.f),
      mSoundVolume(10.f) {
}

SettingsSingleton& SettingsSingleton::getInstance() {
    static SettingsSingleton instance;
    return instance;
}

void SettingsSingleton::setCharacterType(int type) {
    mCharacterType = type;
}

int SettingsSingleton::getCharacterType() {
    return mCharacterType;
}

void SettingsSingleton::setCurrentLevelNumber(int level) {
    mCurrentLevelNumber = level;
}

int SettingsSingleton::getCurrentLevelNumber() {
    return mCurrentLevelNumber;
}

void SettingsSingleton::setMusicVolume(float volume) {
    if (volume < 0.f) {
        volume = 0.f;
    } else if (volume > 100.f) {
        volume = 100.f;
    }
    mMusicVolume = volume;
    mMusicPlayer->setVolume(mMusicVolume);
}

float SettingsSingleton::getMusicVolume() {
    return mMusicVolume;
}

void SettingsSingleton::setSoundVolume(float volume) {
    if (volume < 0.f) {
        volume = 0.f;
    } else if (volume > 100.f) {
        volume = 100.f;
    }
    mSoundVolume = volume;
    mSoundPlayer->setVolume(mSoundVolume);
}

float SettingsSingleton::getSoundVolume() {
    return mSoundVolume;
}

void SettingsSingleton::setSoundPlayer(SoundPlayer* soundPlayer) {
    mSoundPlayer = soundPlayer;
    mSoundPlayer->setVolume(mSoundVolume);
}

void SettingsSingleton::setMusicPlayer(MusicPlayer* musicPlayer) {
    mMusicPlayer = musicPlayer;
    mMusicPlayer->setVolume(mMusicVolume);
}
