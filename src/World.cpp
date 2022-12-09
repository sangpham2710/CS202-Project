#include "World.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <algorithm>
#include <cmath>
#include <limits>

#include "Constants.hpp"

World::World(sf::RenderWindow& window, FontHolder& fonts)
    : mWindow(window),
      mWorldView(window.getDefaultView()),
      mFonts(fonts),
      mTextures(),
      mSceneGraph(),
      mSceneLayers(),
      mWorldBounds(0.f, 0.f, mWorldView.getSize().x + 400,
                   mWorldView.getSize().y),
      mSpawnPosition(mWorldView.getSize().x / 2.f,
                     Constants::LANE_HEIGHT / 2.f),
      mViewPosition(mWorldView.getSize().x / 2.f, mWorldView.getSize().y / 2.f),
      mPlayerCharacter(nullptr) {
    loadTextures();
    buildScene();
    mWorldView.setCenter(mViewPosition);
}

void World::update(sf::Time dt) {
    destroyObstaclesOutsideView();
    mPlayerCharacter->setVelocity(0.f, 0.f);
    while (!mCommandQueue.isEmpty()) {
        mSceneGraph.onCommand(mCommandQueue.pop(), dt);
    }
    mSceneGraph.removeWrecks();
    mSceneGraph.update(dt, mCommandQueue);
    adaptPlayerPosition();
}

void World::draw() {
    mWindow.setView(mWorldView);
    mWindow.draw(mSceneGraph);
}

CommandQueue& World::getCommandQueue() {
    return mCommandQueue;
}

void World::loadTextures() {
    mTextures.load(Textures::Background, "./assets/textures/background.png");
    mTextures.load(Textures::Character, "./assets/textures/character.png");
    mTextures.load(Textures::BlueBusLeft,
                   "./assets/textures/vehicles/blue-bus-left.png");
    mTextures.load(Textures::BlueBusRight,
                   "./assets/textures/vehicles/blue-bus-right.png");
    mTextures.load(Textures::BlueCarLeft,
                   "./assets/textures/vehicles/blue-car-left.png");
    mTextures.load(Textures::BlueCarRight,
                   "./assets/textures/vehicles/blue-car-right.png");
    mTextures.load(Textures::GrayCarLeft,
                   "./assets/textures/vehicles/gray-car-left.png");
    mTextures.load(Textures::GrayCarRight,
                   "./assets/textures/vehicles/gray-car-right.png");
    mTextures.load(Textures::NewVanLeft,
                   "./assets/textures/vehicles/new-van-left.png");
    mTextures.load(Textures::NewVanRight,
                   "./assets/textures/vehicles/new-van-right.png");
    mTextures.load(Textures::OldVanLeft,
                   "./assets/textures/vehicles/old-van-left.png");
    mTextures.load(Textures::OldVanRight,
                   "./assets/textures/vehicles/old-van-right.png");
    mTextures.load(Textures::OrangeBusLeft,
                   "./assets/textures/vehicles/orange-bus-left.png");
    mTextures.load(Textures::OrangeBusRight,
                   "./assets/textures/vehicles/orange-bus-right.png");
    mTextures.load(Textures::PoliceCarLeft,
                   "./assets/textures/vehicles/police-car-left.png");
    mTextures.load(Textures::PoliceCarRight,
                   "./assets/textures/vehicles/police-car-right.png");
    mTextures.load(Textures::RedCarLeft,
                   "./assets/textures/vehicles/red-car-left.png");
    mTextures.load(Textures::RedCarRight,
                   "./assets/textures/vehicles/red-car-right.png");
    mTextures.load(Textures::RedStripedCarLeft,
                   "./assets/textures/vehicles/red-striped-car-left.png");
    mTextures.load(Textures::RedStripedCarRight,
                   "./assets/textures/vehicles/red-striped-car-right.png");
    mTextures.load(Textures::RedTruckLeft,
                   "./assets/textures/vehicles/red-truck-left.png");
    mTextures.load(Textures::RedTruckRight,
                   "./assets/textures/vehicles/red-truck-right.png");
    mTextures.load(Textures::SchoolBusLeft,
                   "./assets/textures/vehicles/school-bus-left.png");
    mTextures.load(Textures::SchoolBusRight,
                   "./assets/textures/vehicles/school-bus-right.png");
    mTextures.load(Textures::WhiteTruckLeft,
                   "./assets/textures/vehicles/white-truck-left.png");
    mTextures.load(Textures::WhiteTruckRight,
                   "./assets/textures/vehicles/white-truck-right.png");
    mTextures.load(Textures::YellowCabLeft,
                   "./assets/textures/vehicles/yellow-cab-left.png");
    mTextures.load(Textures::YellowCabRight,
                   "./assets/textures/vehicles/yellow-cab-right.png");
    mTextures.load(Textures::YellowCarLeft,
                   "./assets/textures/vehicles/yellow-car-left.png");
    mTextures.load(Textures::YellowCarRight,
                   "./assets/textures/vehicles/yellow-car-right.png");

    mTextures.load(Textures::GrassLane, "./assets/textures/lanes/grass-1.png");
    mTextures.load(Textures::Railway, "./assets/textures/lanes/railway-1.png");
    mTextures.load(Textures::RoadSingle,
                   "./assets/textures/lanes/road-single.png");
}

void World::adaptPlayerPosition() {
    sf::FloatRect viewBounds = getViewBounds();

    sf::Vector2f position = mPlayerCharacter->getPosition();
    int halfBlockSize = Constants::BLOCK_SIZE / 2;
    position.x = std::max(position.x, viewBounds.left + halfBlockSize);
    position.x = std::min(position.x,
                          viewBounds.left + viewBounds.width - halfBlockSize);
    position.y = std::max(position.y, viewBounds.top + halfBlockSize);
    position.y = std::min(position.y,
                          viewBounds.top + viewBounds.height - halfBlockSize);
    mPlayerCharacter->setPosition(position);
}

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
    for (std::size_t i = 0; i < LayerCount; ++i) {
        SceneNode::Ptr layer(new SceneNode());
        mSceneLayers[i] = layer.get();
        mSceneGraph.attachChild(std::move(layer));
    }

    sf::Texture& texture = mTextures.get(Textures::Background);
    sf::IntRect textureRect(mWorldBounds);
    texture.setRepeated(true);

    std::unique_ptr<SpriteNode> backgroundSprite(
        new SpriteNode(texture, textureRect));
    backgroundSprite->setPosition(mWorldBounds.left, mWorldBounds.top);
    mSceneLayers[Background]->attachChild(std::move(backgroundSprite));

	std::unique_ptr<Lane> laneNode(
		new Lane(Lane::Type::Grass, Lane::Direction::Left, 100, mTextures));
    laneNode->setPosition(100, 100);
	mSceneLayers[Land]->attachChild(std::move(laneNode));

    std::unique_ptr<Character> character(new Character(mTextures));
    character->setPosition(mSpawnPosition);
    mPlayerCharacter = character.get();
    mSceneLayers[Land]->attachChild(std::move(character));
}

void World::destroyObstaclesOutsideView() {
    Command command;
    command.category = Category::Obstacle;
    command.action = derivedAction<Entity>([this](Entity& e, sf::Time) {
        if (!getBattlefieldBounds().intersects(e.getBoundingRect())) {
            e.destroy();
        }
    });
}

sf::FloatRect World::getViewBounds() const {
    return sf::FloatRect(mWorldView.getCenter() - mWorldView.getSize() / 2.f,
                         mWorldView.getSize());
}

sf::FloatRect World::getBattlefieldBounds() const {
    // Return view bounds + some area at top, where enemies spawn
    sf::FloatRect bounds = getViewBounds();
    bounds.left -= 200;
    bounds.width += 400;
    return bounds;
}
