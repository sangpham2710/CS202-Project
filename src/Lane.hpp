#ifndef LANE_HPP
#define LANE_HPP

#include "SceneNode.hpp"
#include "TrafficLight.hpp"
#include "Obstacle.hpp"

class Lane : public SceneNode {
	public:
		Lane();

		void stopObstables();
		void generateRandomObstacles();
	
	private:
		std::vector<Obstacle> obstacleList;	
		TrafficLight trafficLight;
};

#endif // LANE_HPP