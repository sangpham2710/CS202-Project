#include "World.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <algorithm>
#include <cmath>
#include <limits>

World::World(sf::RenderWindow& window, FontHolder& fonts)
    : mWindow(window),
      mWorldView(window.getDefaultView()),
      mFonts(fonts),
      mTextures(),
      mSceneGraph(),
      mSceneLayers(),
      mWorldBounds(0.f, 0.f, mWorldView.getSize().x, 2000.f),
      mSpawnPosition(mWorldView.getSize().x / 2.f,
                     mWorldBounds.height - mWorldView.getSize().y / 2.f) {
    loadTextures();
    buildScene();
}

void World::update(sf::Time dt) {
}

void World::draw() {
    mWindow.setView(mWorldView);
    mWindow.draw(mSceneGraph);
}

CommandQueue& World::getCommandQueue() {
    return mCommandQueue;
}

void World::loadTextures() {
    mTextures.load(Textures::Eagle, "Media/Textures/Eagle.png");
    mTextures.load(Textures::Raptor, "Media/Textures/Raptor.png");
    mTextures.load(Textures::Avenger, "Media/Textures/Avenger.png");
    mTextures.load(Textures::Desert, "Media/Textures/Desert.png");

    mTextures.load(Textures::Bullet, "Media/Textures/Bullet.png");
    mTextures.load(Textures::Missile, "Media/Textures/Missile.png");

    mTextures.load(Textures::HealthRefill, "Media/Textures/HealthRefill.png");
    mTextures.load(Textures::MissileRefill, "Media/Textures/MissileRefill.png");
    mTextures.load(Textures::FireSpread, "Media/Textures/FireSpread.png");
    mTextures.load(Textures::FireRate, "Media/Textures/FireRate.png");
}

// void World::adaptPlayerPosition() {
//     // Keep player's position inside the screen bounds, at least
//     borderDistance
//     // units from the border
//     sf::FloatRect viewBounds = getViewBounds();
//     const float borderDistance = 40.f;

//     sf::Vector2f position = mPlayerAircraft->getPosition();
//     position.x = std::max(position.x, viewBounds.left + borderDistance);
//     position.x = std::min(position.x,
//                           viewBounds.left + viewBounds.width -
//                           borderDistance);
//     position.y = std::max(position.y, viewBounds.top + borderDistance);
//     position.y = std::min(position.y,
//                           viewBounds.top + viewBounds.height -
//                           borderDistance);
//     mPlayerAircraft->setPosition(position);
// }

bool matchesCategories(SceneNode::Pair& colliders, Category::Type type1,
                       Category::Type type2) {
    unsigned int category1 = colliders.first->getCategory();
    unsigned int category2 = colliders.second->getCategory();

    // Make sure first pair entry has category type1 and second has type2
    if (type1 & category1 && type2 & category2) {
        return true;
    } else if (type1 & category2 && type2 & category1) {
        std::swap(colliders.first, colliders.second);
        return true;
    } else {
        return false;
    }
}

void World::handleCollisions() {
}

void World::buildScene() {
}

void World::destroyEntitiesOutsideView() {
}

sf::FloatRect World::getViewBounds() const {
    return sf::FloatRect(mWorldView.getCenter() - mWorldView.getSize() / 2.f,
                         mWorldView.getSize());
}

sf::FloatRect World::getBattlefieldBounds() const {
    // Return view bounds + some area at top, where enemies spawn
    sf::FloatRect bounds = getViewBounds();
    bounds.top -= 100.f;
    bounds.height += 100.f;

    return bounds;
}
