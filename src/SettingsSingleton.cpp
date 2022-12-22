#include "SettingsSingleton.hpp"

SettingsSingleton::SettingsSingleton()
    : mCharacterType(0),
      mCurrentLevelNumber(1),
      mMusicVolume(25.f),
      mSoundVolume(25.f) {
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
    mMusicVolume = volume;
}

float SettingsSingleton::getMusicVolume() {
    return mMusicVolume;
}

void SettingsSingleton::setSoundVolume(float volume) {
    mSoundVolume = volume;
}

float SettingsSingleton::getSoundVolume() {
    return mSoundVolume;
}
