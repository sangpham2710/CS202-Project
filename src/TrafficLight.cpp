#include "TrafficLight.hpp"
#include <random>
#include "DataTables.hpp"
#include "ResourceHolder.hpp"
#include "TexturesSingleton.hpp"
#include "Utility.hpp"

TrafficLight::TrafficLight()
    : mCurrentState(State::Green), elapsedTime(sf::seconds(0))
{
    mSprite.setTexture(TexturesSingleton::getInstance().getTextures().get(
        Textures::GreenLight));

    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist13(1, 3); // distribution in range [1, 3]

    switch (dist13(rng))
    {
    case 2:
        mCurrentState = State::Yellow;
        break;
    case 3:
        mCurrentState = State::Red;
        break;
    default://green
        break;
    }

    switch (dist13(rng))
    {
    case 2:
        elapsedTime = sf::seconds(1);
        break;
    case 3:
        elapsedTime = sf::seconds(2);;
        break;
    default://0
        break;
    }
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

int TrafficLight::getState()
{
    if (mCurrentState == State::Red)
        return 0;
    if (mCurrentState == State::Yellow)
        return 1;
    if (mCurrentState == State::Green)
        return 2;
}