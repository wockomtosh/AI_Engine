#pragma once

#include <queue>
#include <vector>
#include <set>
#include <functional>

#include "Heuristic.h"
#include "DijkstraHeuristic.h"
#include "Graph/DirectedGraph.h"
#include "Graph/DirectedWeightedEdge.h"

struct NodeRecord {
	int nodeID;
	DirectedWeightedEdge incomingEdge;
	float costSoFar;
	float heuristicEstimate;

	NodeRecord() :
		nodeID(0), incomingEdge(DirectedWeightedEdge::NULL_EDGE), costSoFar(0), heuristicEstimate(0) {}
	NodeRecord(int nodeID, DirectedWeightedEdge incomingEdge, float costSoFar, float heuristicEstimate) :
		nodeID(nodeID), incomingEdge(incomingEdge), costSoFar(costSoFar), heuristicEstimate(heuristicEstimate) {}

	bool operator>(NodeRecord other);
	bool operator<(NodeRecord other);
	bool operator==(NodeRecord other);

	//used for std::push_heap and related functions
	bool operator()(const NodeRecord& a, const NodeRecord& b);
};

//Should this be a class with a static function, or a namespace, or a class that we create to hold the graph and heuristic and everything?
namespace Pathfinder {
	//Set Heuristic to nullptr to use Dijkstra's algorithm.
	std::vector<DirectedWeightedEdge> findPath(int start, int goal, DirectedGraph* graph, Heuristic* heuristic, bool printNodesVisited = false);
};