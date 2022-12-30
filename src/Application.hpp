#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Time.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>
#include <TGUI/Core.hpp>

#include "MusicPlayer.hpp"
#include "Player.hpp"
#include "ResourceHolder.hpp"
#include "ResourceIdentifiers.hpp"
#include "SoundPlayer.hpp"
#include "StateStack.hpp"

class Application {
   public:
    Application();
    void run();


   private:
    void processInput();
    void update(sf::Time dt);
    void render();
    void registerStates();


   private:
    static const sf::Time TimePerFrame;

    sf::RenderWindow mWindow;
    TextureHolder mTextures;
    FontHolder mFonts;
    MusicPlayer mMusic;
    SoundPlayer mSounds;

    Player mPlayer;

    StateStack mStateStack;
};