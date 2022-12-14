#include "TrafficLight.hpp"

#include "DataTables.hpp"
#include "ResourceHolder.hpp"
#include "TexturesSingleton.hpp"
#include "Utility.hpp"

TrafficLight::TrafficLight()
    : mCurrentState(State::Green), elapsedTime(sf::seconds(0)) {
    mSprite.setTexture(TexturesSingleton::getInstance().getTextures().get(
        Textures::GreenLight));
}


void TrafficLight::updateCurrent(sf::Time dt, CommandQueue& commands) {
    elapsedTime += dt;
    if (mCurrentState == State::Green && elapsedTime > sf::seconds(3)) {
        elapsedTime = sf::seconds(0);
        mCurrentState = State::Yellow;
        mSprite.setTexture(TexturesSingleton::getInstance().getTextures().get(
            Textures::YellowLight));
    }
    if (mCurrentState == State::Yellow && elapsedTime > sf::seconds(3)) {
        elapsedTime = sf::seconds(0);
        mCurrentState = State::Red;
        mSprite.setTexture(TexturesSingleton::getInstance().getTextures().get(
            Textures::RedLight));
    }
    if (mCurrentState == State::Red && elapsedTime > sf::seconds(3)) {
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