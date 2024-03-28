#pragma once
#include "Heuristic.h"
#include "Graph/DirectedGraph.h"
#include "Pathfinder.h"

//The idea with this heuristic is that I made a smaller, simpler graph based on my larger graph.
//I'll solve that graph with Dijkstra's and that will be the heuristic.
//This also only works with my handmade graph, since the graph here is handmade too.
//I'm fairly confident that this is consistent and admissible, but I can't prove it.
class SmallerGraphHeuristic : public Heuristic {
	int goal;
	std::map<int, int> largeGraphToSmall;
	DirectedGraph* smallerGraph;

public:
	SmallerGraphHeuristic(int goal);
	~SmallerGraphHeuristic();

	float estimate(int nodeID);
};