#pragma once

#include "SceneNode.h"

class Entity : public SceneNode {
	public:
		Entity();

		void setVelocity(sf::Vector2f velocity);	
		void setVelocity(float vx, float vy);
		void accelerate(sf::Vector2f velocity);
		void accelerate(float vx, float vy);
		sf::Vector2f getVelocity() const;

		~Entity();
	protected:
		virtual void updateCurrent(sf::Time dt);

	private:
		sf::Vector2f mVelocity;
};