#pragma once

#include "ResourceIdentifiers.hpp"
#include "SceneNode.hpp"

class SoundPlayer;

class SoundNode : public SceneNode {
   public:
    explicit SoundNode(SoundPlayer& player);
    void playSound(SoundEffect::ID sound, sf::Vector2f position);

    virtual unsigned int getCategory() const;


   private:
    SoundPlayer& mSounds;
};
