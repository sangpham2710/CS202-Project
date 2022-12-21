#include "World.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <algorithm>
#include <cmath>
#include <limits>
#include <map>
#include <random>
#include <vector>

#include "Constants.hpp"
#include "TexturesSingleton.hpp"
#include "Utility.hpp"



World::World(sf::RenderWindow& window, FontHolder& fonts)
    : mWindow(window),
      mWorldView(window.getDefaultView()),
      mFonts(fonts),
      mSceneGraph(),
      mSceneLayers(),
      mWorldBounds(0.f, 0.f, mWorldView.getSize().x + 400,
                   mWorldView.getSize().y),
      mSpawnPosition(Constants::BLOCK_SIZE * 8 + Constants::BLOCK_SIZE / 2,
                     Constants::LANE_HEIGHT / 2.f),
      mViewPosition(mWorldView.getSize().x / 2.f, mWorldView.getSize().y / 2.f),
      mPlayerCharacter(nullptr),
      mLevel(nullptr) {
  loadTextures();
  buildScene();
  mWorldView.setCenter(mViewPosition);
}

void World::update(sf::Time dt) {
  destroyObstaclesOutsideView();
  while (!mCommandQueue.isEmpty()) {
    mSceneGraph.onCommand(mCommandQueue.pop(), dt);
  }
  handleCollisions();
  mSceneGraph.removeWrecks();
  mSceneGraph.update(dt, mCommandQueue);
  adaptPlayerPosition();
}

void World::draw() {
  mWindow.setView(mWorldView);
  mWindow.draw(mSceneGraph);
}

CommandQueue& World::getCommandQueue() { return mCommandQueue; }

bool World::hasAlivePlayer() const {
  return !mPlayerCharacter->isMarkedForRemoval();
}

void World::loadTextures() {}

void World::adaptPlayerPosition() {
  sf::FloatRect viewBounds = getViewBounds();

  sf::Vector2f position = mPlayerCharacter->getPosition();
  int halfBlockSize = Constants::BLOCK_SIZE / 2;
  position.x = std::max(position.x, viewBounds.left + halfBlockSize);
  position.x =
      std::min(position.x, viewBounds.left + viewBounds.width - halfBlockSize);
  position.y = std::max(position.y, viewBounds.top + halfBlockSize);
  position.y =
      std::min(position.y, viewBounds.top + viewBounds.height - halfBlockSize);
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

#include <iostream>

void World::handleCollisions() {
  std::set<SceneNode::Pair> collisionPairs;
  mSceneGraph.checkSceneCollision(mSceneGraph, collisionPairs);

  for (SceneNode::Pair pair : collisionPairs) {
    if (matchesCategories(pair, Category::PlayerCharacter,
                          Category::Obstacle)) {
      auto& character = static_cast<Character&>(*pair.first);
      auto& obstacle = static_cast<Obstacle&>(*pair.second);

      auto characterPosition = character.getWorldPosition();
      auto obstaclePosition = obstacle.getWorldPosition() +
                              sf::Vector2f(obstacle.getBoundingRect().width,
                                           obstacle.getBoundingRect().height) *
                                  0.5f;
      auto explosionPosition = (obstaclePosition - characterPosition) * 0.5f;
      character.setExplosionPosition(explosionPosition);
      character.destroy();
      obstacle.setTextureWrecked();
      character.setTextureWrecked();
      Command command;
      command.category = Category::Obstacle;
      // stop all obstacles
      command.action =
          derivedAction<Obstacle>([](Obstacle& obstacle, sf::Time) {
            obstacle.setVelocity(0.0f, 0.0f);
          });
      mCommandQueue.push(command);
    }
  }
}

void World::buildScene() {
  for (std::size_t i = 0; i < LayerCount; ++i) {
    SceneNode::Ptr layer(new SceneNode());
    mSceneLayers[i] = layer.get();
    mSceneGraph.attachChild(std::move(layer));
  }
  sf::Texture& texture =
      TexturesSingleton::getInstance().getTextures().get(Textures::Background);
  sf::IntRect textureRect(mWorldBounds);
  texture.setRepeated(true);

  std::unique_ptr<SpriteNode> backgroundSprite(
      new SpriteNode(texture, textureRect));
  backgroundSprite->setPosition(mWorldBounds.left, mWorldBounds.top);
  mSceneLayers[Background]->attachChild(std::move(backgroundSprite));

  // level setup start here
  if (mLevel == nullptr) {
    mLevel = std::unique_ptr<Level>(new Level(5));
  } else {
    mLevel->levelUp();
  }
  loadLevel();
  // level startup end here

  std::unique_ptr<Character> character(new Character());
  character->setPosition(mSpawnPosition);
  mPlayerCharacter = character.get();
  mSceneLayers[Land]->attachChild(std::move(character));
}

void World::destroyObstaclesOutsideView() {
  Command command;
  command.category = Category::Obstacle;
  command.action = derivedAction<Obstacle>([this](Entity& e, sf::Time) {
    if (!getBattlefieldBounds().intersects(e.getBoundingRect())) {
      e.destroy();
    }
  });
  mCommandQueue.push(command);
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

void generateListLane(std::map<Lane::Type, std::vector<Lane::Type>>& listLane) {
  listLane[Lane::Type::Grass] = {Lane::Type::LilyPadAbove,
                                 Lane::Type::PavementAbove, Lane::Type::Railway,
                                 Lane::Type::RoadAbove, Lane::Type::RoadSingle};

  listLane[Lane::Type::LilyPadAbove] = {Lane::Type::LilyPadBelow};

  listLane[Lane::Type::LilyPadBelow] = {
      Lane::Type::Grass, Lane::Type::PavementAbove, Lane::Type::Railway,
      Lane::Type::RoadAbove, Lane::Type::RoadSingle};

  listLane[Lane::Type::LilyPadSingle] = {
      Lane::Type::Grass, Lane::Type::PavementAbove, Lane::Type::Railway,
      Lane::Type::RoadAbove, Lane::Type::RoadSingle};

  listLane[Lane::Type::PavementAbove] = {Lane::Type::PavementBelow};

  listLane[Lane::Type::PavementBelow] = {
      Lane::Type::Grass,   Lane::Type::LilyPadAbove, Lane::Type::LilyPadSingle,
      Lane::Type::Railway, Lane::Type::RoadAbove,    Lane::Type::RoadSingle};
  listLane[Lane::Type::Railway] = {
      Lane::Type::Grass,         Lane::Type::LilyPadAbove,
      Lane::Type::LilyPadSingle, Lane::Type::PavementAbove,
      Lane::Type::RoadAbove,     Lane::Type::RoadSingle};

  listLane[Lane::Type::RoadAbove] = {Lane::Type::RoadMiddle,
                                     Lane::Type::RoadBelow};

  listLane[Lane::Type::RoadMiddle] = {Lane::Type::RoadBelow,
                                      Lane::Type::RoadMiddle};

  listLane[Lane::Type::RoadBelow] = {
      Lane::Type::Grass, Lane::Type::LilyPadAbove, Lane::Type::LilyPadSingle,
      Lane::Type::PavementAbove, Lane::Type::Railway};

  listLane[Lane::Type::RoadSingle] = {
      Lane::Type::Grass, Lane::Type::LilyPadAbove, Lane::Type::LilyPadSingle,
      Lane::Type::PavementAbove, Lane::Type::Railway};
}

void getRandomNextState(
    Lane::Type& currentState, Lane::Direction& dt,
    std::map<Lane::Type, std::vector<Lane::Type>>& listLane) {
  int randomNextState = randomInt(listLane[currentState].size());
  int randomDirection = randomInt(2);
  if (randomDirection == 0)
    dt = Lane::Direction::Left;
  else
    dt = Lane::Direction::Right;
  currentState = listLane[currentState][randomNextState];
}


void World::loadLevel() {
  float speed = mLevel.get()->caculateSpeed();
  int spawnRate = mLevel.get()->caculateSpawnRate();

  std::map<Lane::Type, std::vector<Lane::Type>> listLane;
  generateListLane(listLane);

  Lane::Type currentState = Lane::Type::Grass ;
  int numLane = 12;
  Lane::Direction dt;
  getRandomNextState(currentState, dt, listLane);
  
  for (int i = 0; i < numLane; i++) {
    std::unique_ptr<Lane> laneNodeA(
        new Lane(currentState, dt, speed));
    laneNodeA->setPosition(0, i * Constants::BLOCK_SIZE);
    laneNodeA.get()->setSpawnRate(spawnRate);
    mSceneLayers[Land]->attachChild(std::move(laneNodeA));
    getRandomNextState(currentState, dt, listLane);
  }
}


