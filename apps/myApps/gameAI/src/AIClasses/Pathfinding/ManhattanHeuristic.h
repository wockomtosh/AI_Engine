#pragma once
#include "Heuristic.h"
#include "Graph/TileGraph.h"

class ManhattanHeuristic : public Heuristic {
private:
	TileGraph* graph;
	int goal;
	Vector2 goalNodeCoordinate;

public:
	ManhattanHeuristic(int goal, TileGraph* graph);

	float estimate(int nodeID);
};