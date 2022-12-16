#include "SettingsSingleton.hpp"

SettingsSingleton::SettingsSingleton() : characterType(0) {
}

SettingsSingleton& SettingsSingleton::getInstance() {
    static SettingsSingleton instance;
    return instance;
}

void SettingsSingleton::setCharacterType(int type) {
    characterType = type;
}

int SettingsSingleton::getCharacterType() {
    return characterType;
}