#pragma once

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/System/NonCopyable.hpp>
#include <array>
#include <queue>

#include "Command.hpp"
#include "CommandQueue.hpp"
#include "ResourceHolder.hpp"
#include "ResourceIdentifiers.hpp"
#include "SceneNode.hpp"
#include "SpriteNode.hpp"

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

   private:
    void loadTextures();
    void handleCollisions();

    void buildScene();
    void destroyEntitiesOutsideView();
    sf::FloatRect getViewBounds() const;
    sf::FloatRect getBattlefieldBounds() const;

   private:
    enum Layer { Background, Lane, LayerCount };

   private:
    sf::RenderWindow& mWindow;
    sf::View mWorldView;
    TextureHolder mTextures;
    FontHolder& mFonts;

    SceneNode mSceneGraph;
    std::array<SceneNode*, LayerCount> mSceneLayers;
    CommandQueue mCommandQueue;

    sf::FloatRect mWorldBounds;
    sf::Vector2f mSpawnPosition;
};
