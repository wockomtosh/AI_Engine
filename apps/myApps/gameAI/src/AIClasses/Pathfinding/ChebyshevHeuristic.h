#pragma once
#include "Heuristic.h"
#include "Graph/TileGraph.h"

//This underestimates diagonals by a lot, considering them to be the same cost as moving sideways
//I'm curious to see if it encourages diagonal travel or not.
class ChebyshevHeuristic : public Heuristic {
private:
	TileGraph* graph;
	int goal;
	Vector2 goalNodeCoordinate;

public:
	ChebyshevHeuristic(int goal, TileGraph* graph) :
		goal(goal), graph(graph)
	{
		goalNodeCoordinate = graph->getNodeCoordinateFromNode(goal);
	}

	float estimate(int nodeID)
	{
		Vector2 nodeCoordinate = graph->getNodeCoordinateFromNode(nodeID);
		int xDist = abs(nodeCoordinate.x - goalNodeCoordinate.x);
		int yDist = abs(nodeCoordinate.y - goalNodeCoordinate.y);

		return std::max(xDist, yDist);
	}
};