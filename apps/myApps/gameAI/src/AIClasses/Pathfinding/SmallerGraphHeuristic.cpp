#include "SmallerGraphHeuristic.h"

SmallerGraphHeuristic::SmallerGraphHeuristic(int goal) : goal(goal)
{
	//We want to map our large graph of 17 nodes to a smaller graph of 5 nodes
	largeGraphToSmall[0] = 0;
	largeGraphToSmall[1] = 0;
	largeGraphToSmall[2] = 0;
	largeGraphToSmall[3] = 0;
	largeGraphToSmall[4] = 0;
	largeGraphToSmall[5] = 1;
	largeGraphToSmall[6] = 1;
	largeGraphToSmall[7] = 1;
	largeGraphToSmall[8] = 1;
	largeGraphToSmall[9] = 4;
	largeGraphToSmall[10] = 2;
	largeGraphToSmall[11] = 1;
	largeGraphToSmall[12] = 3;
	largeGraphToSmall[13] = 3;
	largeGraphToSmall[14] = 3;
	largeGraphToSmall[15] = 4;
	largeGraphToSmall[16] = 4;

	//Setup the edges of our smaller graph
	std::map<int, std::vector<DirectedWeightedEdge>> edges;
	const int numNodes = 5;
	for (int i = 0; i < numNodes; i++)
	{
		edges[i] = std::vector<DirectedWeightedEdge>();
	}

	edges[0].push_back(DirectedWeightedEdge(8, 0, 2));
	edges[0].push_back(DirectedWeightedEdge(8, 0, 4));
	edges[0].push_back(DirectedWeightedEdge(4, 0, 1));
	edges[1].push_back(DirectedWeightedEdge(4, 1, 0));
	edges[1].push_back(DirectedWeightedEdge(8, 1, 3));
	edges[2].push_back(DirectedWeightedEdge(8, 2, 0));
	edges[2].push_back(DirectedWeightedEdge(7, 2, 3));
	edges[2].push_back(DirectedWeightedEdge(5, 2, 4));
	edges[3].push_back(DirectedWeightedEdge(8, 3, 1));
	edges[3].push_back(DirectedWeightedEdge(7, 3, 2));
	edges[3].push_back(DirectedWeightedEdge(5, 3, 4));
	edges[4].push_back(DirectedWeightedEdge(8, 4, 0));
	edges[4].push_back(DirectedWeightedEdge(5, 4, 2));
	edges[4].push_back(DirectedWeightedEdge(5, 4, 3));

	smallerGraph = new DirectedGraph(edges);
}

SmallerGraphHeuristic::~SmallerGraphHeuristic() {}

float SmallerGraphHeuristic::estimate(int nodeID)
{
	//map our start and end onto the smaller graph
	int start = largeGraphToSmall[nodeID];
	int end = largeGraphToSmall[goal];

	//find the path on our smaller graph with Dijkstra's
	std::vector<DirectedWeightedEdge> smallerPath = Pathfinder::findPath(start, end, smallerGraph, nullptr);

	//Calculate the path length
	int pathLength = 0;
	for (DirectedWeightedEdge edge : smallerPath)
	{
		pathLength += edge.weight;
	}

	return pathLength;
}
