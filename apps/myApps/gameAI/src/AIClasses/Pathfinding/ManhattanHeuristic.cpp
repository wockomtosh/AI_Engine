#include "ManhattanHeuristic.h"

ManhattanHeuristic::ManhattanHeuristic(int goal, TileGraph* graph) :
	goal(goal), graph(graph) 
{
	goalNodeCoordinate = graph->getNodeCoordinateFromNode(goal);
}

float ManhattanHeuristic::estimate(int nodeID)
{
	Vector2 nodeCoordinate = graph->getNodeCoordinateFromNode(nodeID);
	int xDist = abs(nodeCoordinate.x - goalNodeCoordinate.x);
	int yDist = abs(nodeCoordinate.y - goalNodeCoordinate.y);

	//The weights for all of the edges in the tile graph are 1, otherwise we'd need to scale this differently
	return xDist + yDist;
}
