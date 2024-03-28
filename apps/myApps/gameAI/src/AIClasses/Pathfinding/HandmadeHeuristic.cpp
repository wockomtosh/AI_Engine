#include "HandmadeHeuristic.h"
#include <math.h>

std::vector<std::pair<float, float>> generateCoordinates()
{
	std::vector<std::pair<float, float>> nodeCoordinates;

	nodeCoordinates.push_back(std::make_pair(3, 0));
	nodeCoordinates.push_back(std::make_pair(6, 0));
	nodeCoordinates.push_back(std::make_pair(10, 0));
	nodeCoordinates.push_back(std::make_pair(3, 1));
	nodeCoordinates.push_back(std::make_pair(6, 1));
	nodeCoordinates.push_back(std::make_pair(10, 2));
	nodeCoordinates.push_back(std::make_pair(10, 6));
	nodeCoordinates.push_back(std::make_pair(13, 6));
	nodeCoordinates.push_back(std::make_pair(16, 4));
	nodeCoordinates.push_back(std::make_pair(4, 8));
	nodeCoordinates.push_back(std::make_pair(8, 8));
	nodeCoordinates.push_back(std::make_pair(13, 8));
	nodeCoordinates.push_back(std::make_pair(14, 15));
	nodeCoordinates.push_back(std::make_pair(10, 16));
	nodeCoordinates.push_back(std::make_pair(5, 12));
	nodeCoordinates.push_back(std::make_pair(0, 9));
	nodeCoordinates.push_back(std::make_pair(0, 6));

	return nodeCoordinates;
}

HandmadeHeuristic::HandmadeHeuristic(int goal) : goal(goal)
{
	nodeCoordinates = generateCoordinates();
}

float calculateDistance(std::pair<float, float> source, std::pair<float, float> destination)
{
	float xvalue = pow(destination.first - source.first, 2);
	float yvalue = pow(destination.second - source.second, 2);
	return sqrt(xvalue + yvalue);
}

float HandmadeHeuristic::estimate(int nodeID)
{
	return calculateDistance(nodeCoordinates[nodeID], nodeCoordinates[goal]);
}
