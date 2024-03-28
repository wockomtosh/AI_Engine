#pragma once
#include "Heuristic.h"
#include "Graph/DirectedGraph.h"

//This class can only be used with the HandmadeGraph
//This uses a handmade estimated coordinate system for that graph
//It often underestimates because I tried to use short paths to calculate the coordinate system
//But I can't be positive because State Street makes certain paths much shorter time-wise
class HandmadeHeuristic : public Heuristic {
private:
	std::vector<std::pair<float, float>> nodeCoordinates;
	int goal;

public:
	HandmadeHeuristic(int goal);

	float estimate(int nodeID);
};