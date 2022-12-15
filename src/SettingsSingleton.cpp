#include "SettingsSingleton.hpp"

SettingsSingleton::SettingsSingleton() : mTextures() {
    
}

SettingsSingleton& SettingsSingleton::getInstance() {
    static SettingsSingleton instance;
    return instance;    
}

TextureHolder& SettingsSingleton::getTextures() {
    return mTextures;
}

void SettingsSingleton::setCharacterType(int type) {
    characterType = type;
}

int SettingsSingleton::getCharacterType() {
    return characterType;
}