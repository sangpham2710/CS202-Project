#include "SettingsSingleton.hpp"

SettingsSingleton::SettingsSingleton()
    : mCharacterType(0),
      mCurrentLevelNumber(1),
      mMusicVolume(10.f),
      mSoundVolume(10.f),
      mSoundPlayer(nullptr),
      mMusicPlayer(nullptr),
      mIsLevelLoaded(false),
      mLoadingLevelFilename(""),
      mIsLevelSaving(false) {
}

SettingsSingleton& SettingsSingleton::getInstance() {
    static SettingsSingleton instance;
    return instance;
}

void SettingsSingleton::setCharacterType(int type) {
    mCharacterType = type;
}

int SettingsSingleton::getCharacterType() const {
    return mCharacterType;
}

void SettingsSingleton::setCurrentLevelNumber(int level) {
    mCurrentLevelNumber = level;
}

int SettingsSingleton::getCurrentLevelNumber() const {
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

float SettingsSingleton::getMusicVolume() const {
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

float SettingsSingleton::getSoundVolume() const {
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

void SettingsSingleton::setIsLevelLoaded(bool isLoaded) {
    mIsLevelLoaded = isLoaded;
}

bool SettingsSingleton::getIsLevelLoaded() const {
    return mIsLevelLoaded;
}

void SettingsSingleton::setLoadingLevelFilename(const std::string& filename) {
    mLoadingLevelFilename = filename;
}

std::string SettingsSingleton::getLoadingLevelFilename() const {
    return mLoadingLevelFilename;
}

void SettingsSingleton::setIsLevelSaving(bool isSaving) {
    mIsLevelSaving = isSaving;
}

bool SettingsSingleton::getIsLevelSaving() const {
    return mIsLevelSaving;
}
