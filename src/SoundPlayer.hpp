#pragma once

#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/System/NonCopyable.hpp>
#include <SFML/System/Vector2.hpp>
#include <list>

#include "ResourceHolder.hpp"
#include "ResourceIdentifiers.hpp"


class SoundPlayer : private sf::NonCopyable {
   public:
    SoundPlayer();

    void play(SoundEffect::ID effect);
    void play(SoundEffect::ID effect, sf::Vector2f position);

    void removeStoppedSounds();
    void setListenerPosition(sf::Vector2f position);
    sf::Vector2f getListenerPosition() const;
    void setVolume(float volume);

   private:
    SoundBufferHolder mSoundBuffers;
    std::list<sf::Sound> mSounds;
    float mVolume;
};