#include "Player.hpp"

#include <algorithm>
#include <map>
#include <string>

#include "Character.hpp"
#include "CommandQueue.hpp"
#include "Constants.hpp"

using namespace std::placeholders;

// class CharacterMover {
//    public:
//     CharacterMover(float vx, float vy) : mVelocity{vx / 0.3, vy / 0.3} {}
//     void operator()(Character& character, sf::Time) const {
//         character.setVelocity(mVelocity);
//         // 1s finish jump
//         // 4 frames
//         // 64 pixel jump
//         // move per dt: 1/60 * 64
//         while (1) {
//             if (mVelocity.x == 0 && mVelocity.y < 0) {
//                 character.setAnimation(0);
//                 break;
//             }
//             if (mVelocity.x == 0 && mVelocity.y > 0) {
//                 character.setAnimation(1);
//                 break;
//             }
//             if (mVelocity.x < 0 && mVelocity.y == 0) {
//                 character.setAnimation(2);
//                 break;
//             }
//             if (mVelocity.x > 0 && mVelocity.y == 0) {
//                 character.setAnimation(3);
//                 break;
//             }
//         }
//     }

//    private:
//     sf::Vector2f mVelocity;
// };

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
    mActionBinding[MoveLeft].action = derivedAction<Character>(
        [this](Character& c, sf::Time dt) { c.moveLeft(); });

    mActionBinding[MoveRight].action = derivedAction<Character>(
        [this](Character& c, sf::Time dt) { c.moveRight(); });

    mActionBinding[MoveUp].action = derivedAction<Character>(
        [this](Character& c, sf::Time dt) { c.moveUp(); });

    mActionBinding[MoveDown].action = derivedAction<Character>(
        [this](Character& c, sf::Time dt) { c.moveDown(); });
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
