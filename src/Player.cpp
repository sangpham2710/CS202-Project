#include "Player.hpp"

#include <algorithm>
#include <map>
#include <string>

#include "Character.hpp"
#include "CommandQueue.hpp"
#include "Constants.hpp"

using namespace std::placeholders;

class CharacterMover {
   public:
    CharacterMover(float vx, float vy) : mVelocity{vx, vy} {}
    void operator()(Character& character, sf::Time) const {
        character.move(mVelocity);
    }

   private:
    sf::Vector2f mVelocity;
};

Player::Player() : mCurrentMissionStatus(MissionRunning) {
    // Set initial key bindings
    mKeyBinding[sf::Keyboard::Left] = MoveLeft;
    mKeyBinding[sf::Keyboard::Right] = MoveRight;
    mKeyBinding[sf::Keyboard::Up] = MoveUp;
    mKeyBinding[sf::Keyboard::Down] = MoveDown;

    // Set initial action bindings
    initializeActions();

    // Assign all categories to player's aircraft
    for (auto& pair : mActionBinding)
        pair.second.category = Category::PlayerCharacter;
}

void Player::handleEvent(const sf::Event& event, CommandQueue& commands) {
    if (event.type == sf::Event::KeyPressed) {
        // Check if pressed key appears in key binding, trigger command if so
        auto found = mKeyBinding.find(event.key.code);
        if (found != mKeyBinding.end() && !isRealtimeAction(found->second))
            commands.push(mActionBinding[found->second]);
    }
}

void Player::handleRealtimeInput(CommandQueue& commands) {
    // Traverse all assigned keys and check if they are pressed
    for (auto pair : mKeyBinding) {
        // If key is pressed, lookup action and trigger corresponding command
        if (sf::Keyboard::isKeyPressed(pair.first) &&
            isRealtimeAction(pair.second))
            commands.push(mActionBinding[pair.second]);
    }
}

void Player::assignKey(Action action, sf::Keyboard::Key key) {
    // Remove all keys that already map to action
    for (auto itr = mKeyBinding.begin(); itr != mKeyBinding.end();) {
        if (itr->second == action)
            mKeyBinding.erase(itr++);
        else
            ++itr;
    }

    // Insert new binding
    mKeyBinding[key] = action;
}

sf::Keyboard::Key Player::getAssignedKey(Action action) const {
    for (auto pair : mKeyBinding) {
        if (pair.second == action) return pair.first;
    }

    return sf::Keyboard::Unknown;
}

void Player::setMissionStatus(MissionStatus status) {
    mCurrentMissionStatus = status;
}

Player::MissionStatus Player::getMissionStatus() const {
    return mCurrentMissionStatus;
}

void Player::initializeActions() {
    mActionBinding[MoveLeft].action =
        derivedAction<Character>(CharacterMover(-Constants::BLOCK_SIZE, 0));
    mActionBinding[MoveRight].action =
        derivedAction<Character>(CharacterMover(+Constants::BLOCK_SIZE, 0));
    mActionBinding[MoveUp].action =
        derivedAction<Character>(CharacterMover(0, -Constants::BLOCK_SIZE));
    mActionBinding[MoveDown].action =
        derivedAction<Character>(CharacterMover(0, +Constants::BLOCK_SIZE));
}

bool Player::isRealtimeAction(Action action) {
    switch (action) {
        case MoveLeft:
        case MoveUp:
        case MoveDown:
        case MoveRight:
            return false;

        default:
            return true;
    }
}