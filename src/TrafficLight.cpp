#include "TrafficLight.hpp"

#include <random>

#include "Constants.hpp"
#include "DataTables.hpp"
#include "ResourceHolder.hpp"
#include "TexturesSingleton.hpp"
#include "Utility.hpp"

TrafficLight::TrafficLight()
    : mCurrentState(State::Green), elapsedTime(sf::seconds(0)) {
    mSprite.setTexture(TexturesSingleton::getInstance().getTextures().get(
        Textures::GreenLight));

    float totalLightDuration = Constants::GREEN_LIGHT_DURATION +
                               Constants::YELLOW_LIGHT_DURATION +
                               Constants::RED_LIGHT_DURATION;

    // random a float between 0 and totalLightDuration
    auto randomFloat = [totalLightDuration]() {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> dis(0, totalLightDuration);
        return dis(gen);
    };

    // random a float between 0 and totalLightDuration
    auto startingElapsedTime = randomFloat();

    // set the starting state
    if (startingElapsedTime < Constants::GREEN_LIGHT_DURATION) {
        mCurrentState = State::Green;
        elapsedTime = sf::seconds(startingElapsedTime);
    } else if (startingElapsedTime < Constants::GREEN_LIGHT_DURATION +
                                         Constants::YELLOW_LIGHT_DURATION) {
        mCurrentState = State::Yellow;
        elapsedTime =
            sf::seconds(startingElapsedTime - Constants::GREEN_LIGHT_DURATION);
        mSprite.setTexture(TexturesSingleton::getInstance().getTextures().get(
            Textures::YellowLight));
    } else {
        mCurrentState = State::Red;
        elapsedTime =
            sf::seconds(startingElapsedTime - Constants::GREEN_LIGHT_DURATION -
                        Constants::YELLOW_LIGHT_DURATION);
        mSprite.setTexture(TexturesSingleton::getInstance().getTextures().get(
            Textures::RedLight));
    }
}


void TrafficLight::updateCurrent(sf::Time dt, CommandQueue& commands) {
    elapsedTime += dt;
    if (mCurrentState == State::Green &&
        elapsedTime > sf::seconds(Constants::GREEN_LIGHT_DURATION)) {
        elapsedTime = sf::seconds(0);
        mCurrentState = State::Yellow;
        mSprite.setTexture(TexturesSingleton::getInstance().getTextures().get(
            Textures::YellowLight));
    }
    if (mCurrentState == State::Yellow &&
        elapsedTime > sf::seconds(Constants::YELLOW_LIGHT_DURATION)) {
        elapsedTime = sf::seconds(0);
        mCurrentState = State::Red;
        mSprite.setTexture(TexturesSingleton::getInstance().getTextures().get(
            Textures::RedLight));
    }
    if (mCurrentState == State::Red &&
        elapsedTime > sf::seconds(Constants::RED_LIGHT_DURATION)) {
        elapsedTime = sf::seconds(0);
        mCurrentState = State::Green;
        mSprite.setTexture(TexturesSingleton::getInstance().getTextures().get(
            Textures::GreenLight));
    }
}

void TrafficLight::drawCurrent(sf::RenderTarget& target,
                               sf::RenderStates states) const {
    target.draw(mSprite, states);
}

TrafficLight::State TrafficLight::getState() {
    return mCurrentState;
}