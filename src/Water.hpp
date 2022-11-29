#ifndef WATER_HPP
#define WATER_HPP

#include "Obstacle.hpp"
#include <SFML/Graphics/Sprite.hpp>

class Water {
	public:
		Water(const ResourceHolder& resouce);

		virtual sf::FloatRect getBoundingRect();

	private:
		virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states);
		virtual void updateCurrent(sf::Time dt);

	private:
		sf::Sprite mSprite;
};

#endif // WATER_HPP