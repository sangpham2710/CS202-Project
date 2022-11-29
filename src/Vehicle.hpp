#ifndef VEHICLE_HPP
#define VEHICLE_HPP

#include "Obstacle.hpp"
#include <SFML/Graphics/Sprite.hpp>

class Vehicle : public Obstacle {
	enum Type {
		truck,
		train,
		car
	};

	public:
		Vehicle(Type type, const ResourceHolder& resource);

		unsigned int getType() const;
		virtual sf::FloatRect getBoundingRect();
		virtual bool isMarkedForRemoval() const;

	private:
		virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states);
		virtual void updateCurrent(sf::Time dt);

	private:
		Type mType;
		sf::Sprite mSprite;
};	

#endif // VEHICLE_HPP