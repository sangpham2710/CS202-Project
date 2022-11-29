#ifndef ANIMAL_HPP
#define ANIMAL_HPP

#include "Obstacle.hpp"
#include <SFML/Graphics/Sprite.hpp>

class Animal : public Obstacle {
	enum Type{
		bird,
		dinasour
	};

	public:
		Animal(Type type, const ResourceHolder& resouce, sf::Time time);

		unsigned int getType() const;
		virtual sf::FloatRect getBoundingRect();
		virtual bool isMarkedForRemoval() const;

		void randomTimeChangingDirection();
		void changingDirection();

	private:
		virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states);
		virtual void updateCurrent(sf::Time dt);

	private:
		Type mType;
		sf::Sprite mSprite;
		sf::Time timeBeforeChangingDirection; 
};

#endif // ANIMAL_HPP