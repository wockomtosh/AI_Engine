#pragma once

#include <map>
#include <vector>
#include <algorithm>

#include "DirectedWeightedEdge.h"

class DirectedGraph {
protected:
	std::map<int, std::vector<DirectedWeightedEdge>> edges;

public:
	DirectedGraph() {}
	DirectedGraph(std::map<int, std::vector<DirectedWeightedEdge>> edges);
	~DirectedGraph(){}

	std::vector<DirectedWeightedEdge> getOutgoingEdges(int source);

	static DirectedGraph generateRandomGraph(int numNodes);
	static DirectedGraph generateHandmadeGraph();
};