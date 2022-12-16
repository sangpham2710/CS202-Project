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
#include "ResourceHolder.hpp"
#include "ResourceIdentifiers.hpp"
#include "SceneNode.hpp"
#include "SpriteNode.hpp"
#include "Level.hpp"

// Forward declaration
namespace sf {
class RenderWindow;
}

class World : private sf::NonCopyable {
   public:
    explicit World(sf::RenderWindow& window, FontHolder& fonts);
    void update(sf::Time dt);
    void draw();

    CommandQueue& getCommandQueue();
    bool hasAlivePlayer() const;

   private:
    void loadTextures();
    void adaptPlayerPosition();
    void handleCollisions();

    void buildScene();
    void destroyObstaclesOutsideView();
    sf::FloatRect getViewBounds() const;
    sf::FloatRect getBattlefieldBounds() const;

    void loadLevel();

   private:
    enum Layer { Background, Land, Air, LayerCount };

   private:
    sf::RenderWindow& mWindow;
    sf::View mWorldView;
    FontHolder& mFonts;

    SceneNode mSceneGraph;
    std::array<SceneNode*, LayerCount> mSceneLayers;
    CommandQueue mCommandQueue;

    sf::FloatRect mWorldBounds;
    sf::Vector2f mSpawnPosition;
    sf::Vector2f mViewPosition;
    Character* mPlayerCharacter;
    std::unique_ptr<Level> mLevel;
};
