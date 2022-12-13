#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "Entity.hpp"
#include "ResourceIdentifiers.hpp"

class TrafficLight : public Entity {
public:
	enum class State {
		Green,
		Yellow,
		Red
	};

	TrafficLight();
	

private:
	State mCurrentState;
	sf::Sprite mSprite;
	sf::Time accuTime;
	sf::Time scale;
	virtual void drawCurrent(sf::RenderTarget& target,
		sf::RenderStates states) const override;
	virtual void updateCurrent(sf::Time dt, CommandQueue& commands) override;
};


