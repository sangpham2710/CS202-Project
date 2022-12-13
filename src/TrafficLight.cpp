#include "DataTables.hpp"
#include "ResourceHolder.hpp"
#include "TexturesSingleton.hpp"
#include "Utility.hpp"
#include "TrafficLight.hpp"

TrafficLight::TrafficLight() {

	mSprite = sf::Sprite(TexturesSingleton::getInstance().getTextures().get(Textures::GreenLight));
	sf::Time accuTime = sf::seconds(0);
	mCurrentState = State::Green;
}


void TrafficLight::updateCurrent(sf::Time dt, CommandQueue& commands) {
	accuTime += dt;
	if (mCurrentState == State::Green && accuTime > sf::seconds(3)) {
		accuTime = sf::seconds(0);
		mCurrentState = State::Yellow;
		mSprite = sf::Sprite(TexturesSingleton::getInstance().getTextures().get(Textures::YellowLight));

	}
	 if (mCurrentState == State::Yellow && accuTime > sf::seconds(3)) {
		accuTime = sf::seconds(0);
		mCurrentState = State::Red;
		mSprite = sf::Sprite(TexturesSingleton::getInstance().getTextures().get(Textures::RedLight));

	}
	 if (mCurrentState == State::Red && accuTime > sf::seconds(3)) {
		accuTime = sf::seconds(0);
		mCurrentState = State::Green;
		mSprite = sf::Sprite(TexturesSingleton::getInstance().getTextures().get(Textures::GreenLight));

	}
}

void TrafficLight::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(mSprite, states);
}


//ColorLight::ColorLight(Type type) : mType(type) {
//	if (type == Type::Yellow) {
//		mSprite = sf::Sprite(TexturesSingleton::getInstance().getTextures().get(
//			Textures::YellowLight);
//	}
//	else if (type == Type::Yellow) {
//		mSprite = sf::Sprite(TexturesSingleton::getInstance().getTextures().get(
//			Textures::YellowLight);
//	}
//	else if (type == Type::Red) {
//		mSprite = sf::Sprite(TexturesSingleton::getInstance().getTextures().get(
//			Textures::YellowLight);
//	}
//}