#ifndef TRAFFICLIGHT_HPP
#define TRAFFICLIGHT_HPP

#include "SceneNode.h"

class TrafficLight : public SceneNode {
	public:
		TrafficLight(int state, sf::Time time);

		void setTimeSwitching(sf::Time time);
		sf::Time getTimeSwitching();

		void setCurrentState();
		void getCurrentState();
	
	private:
		int state; // 0: red, 1: yellow, 2: green
		sf::Time timeSwitching;
};

#endif // TRAFFICLIGHT_HPP