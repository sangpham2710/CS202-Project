#ifndef OBSTACLE_HPP
#define OBSTACLE_HPP

#include "Entity.h"

class Obstacle : public Entity {
	public:
		Obstacle();

		bool isMoving();
		int getDirection();
		void setDirection();
		
		void move(sf::Vector2f delta);

		~Obstacle();
	private:
		bool moving; // true: animal, vehicle / false: water,fire-pump 
		int direction; // 0: left, 1: right
};

#endif // OBSTACLE_HPP
