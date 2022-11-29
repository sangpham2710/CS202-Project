#pragma once

#include "SceneNode.h"
#include "TrafficLight.h"
#include "Obstacle.h"

class Lane : public SceneNode {
	public:
		Lane();

		void stopObstables();
		void generateRandomObstacles();
	
	private:
		std::vector<Obstacle> obstacleList;	
		TrafficLight trafficLight;
};