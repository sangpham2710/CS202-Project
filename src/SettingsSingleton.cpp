#include "SettingsSingleton.hpp"

SettingsSingleton::SettingsSingleton()
    : mCharacterType(0), mCurrentLevelNumber(1) {
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