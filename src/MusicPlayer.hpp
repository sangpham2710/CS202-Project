#pragma once

#include <SFML/Audio/Music.hpp>
#include <SFML/System/NonCopyable.hpp>
#include <map>
#include <string>

#include "ResourceHolder.hpp"
#include "ResourceIdentifiers.hpp"

class MusicPlayer : private sf::NonCopyable {
   public:
    MusicPlayer();

    void play(Music::ID theme);
    void stop();

    void setPaused(bool paused);
    void setVolume(float volume);


   private:
    sf::Music mMusic;
    std::map<Music::ID, std::string> mFilenames;
    float mVolume;
};
