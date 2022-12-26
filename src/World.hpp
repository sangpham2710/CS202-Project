#pragma once

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/System/NonCopyable.hpp>
#include <array>
#include <queue>
#include <vector>

#include "Character.hpp"
#include "Command.hpp"
#include "CommandQueue.hpp"
#include "Lane.hpp"
#include "LevelManager.hpp"
#include "ResourceHolder.hpp"
#include "ResourceIdentifiers.hpp"
#include "SceneNode.hpp"
#include "SoundPlayer.hpp"
#include "SpriteNode.hpp"
#include "TrafficLight.hpp"

// Forward declaration
namespace sf {
class RenderWindow;
}

class World : private sf::NonCopyable {
   public:
    friend class LevelManager;
    World(sf::RenderWindow& window, FontHolder& fonts, SoundPlayer& sounds);
    void update(sf::Time dt);
    void draw();

    CommandQueue& getCommandQueue();
    bool hasAlivePlayer() const;
    bool hasPlayerReachedEnd() const;

   private:
    void adaptPlayerPosition();
    void handleCollisions();

    void buildScene();
    void destroyObstaclesOutsideView();
    sf::FloatRect getViewBounds() const;
    sf::FloatRect getBattlefieldBounds() const;

    void loadLevel();

   private:
    enum Layer { Background, LevelLayer, CharacterLayer, LayerCount };

   private:
    sf::RenderWindow& mWindow;
    sf::View mWorldView;
    FontHolder& mFonts;
    SoundPlayer& mSounds;

    SceneNode mSceneGraph;
    std::array<SceneNode*, LayerCount> mSceneLayers;
    CommandQueue mCommandQueue;

    sf::FloatRect mWorldBounds;
    sf::Vector2f mSpawnPosition;
    sf::Vector2f mViewPosition;
    Character* mPlayerCharacter;
    LevelManager mLevelManager;
    bool mIsLevelLoaded;
};
