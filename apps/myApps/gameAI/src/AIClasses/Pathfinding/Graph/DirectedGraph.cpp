#include "DirectedGraph.h"

DirectedGraph::DirectedGraph(std::map<int, std::vector<DirectedWeightedEdge>> edges) :
	edges(edges)
{
}

std::vector<DirectedWeightedEdge> DirectedGraph::getOutgoingEdges(int source)
{
	if (edges.find(source) != edges.end())
	{
		return edges[source];
	}
	return std::vector<DirectedWeightedEdge>();
}

//Random integer from 0 to max-1
int randInt(int max)
{
	return rand() % max + 1;
}

bool edgeExists(std::vector<DirectedWeightedEdge> nodeEdges, int source, int sink)
{
	for (DirectedWeightedEdge edge : nodeEdges)
	{
		if (edge.source == source && edge.sink == sink)
		{
			return true;
		}
	}
	return false;
}

DirectedGraph DirectedGraph::generateRandomGraph(int numNodes)
{
	//This doesn't need to be bidirectional, but it probably shouldn't have loops...
	//The easiest way I can think of to avoid traps is to make it bidirectional...
	//One thing I could do is to have every node connect to the next node (0 to 1, 1 to 2,... numNodes-1 to 0)
	//And then have each of them randomly connect to 1 or 2 other nodes as well.
	const int maxWeight = 1000;
	const int additionalEdges = 3;

	std::map<int, std::vector<DirectedWeightedEdge>> edges;
	
	//initialize map with empty vectors so that we can add an edge to any node at any time
	for (int i = 0; i < numNodes; i++)
	{
		edges[i] = std::vector<DirectedWeightedEdge>();
	}

	for (int i = 0; i < numNodes; i++)
	{
		int randomWeight = randInt(maxWeight);

		//Connect to the next node (both directions)
		if (i == numNodes - 1)
		{
			edges[i].push_back(DirectedWeightedEdge(randomWeight, i, 0));
			edges[0].push_back(DirectedWeightedEdge(randomWeight, 0, i));
		}
		else
		{
			edges[i].push_back(DirectedWeightedEdge(randomWeight, i, i + 1));
			edges[i + 1].push_back(DirectedWeightedEdge(randomWeight, i + 1, i));
		}

		//Generate additional edges
		for (int j = 0; j < additionalEdges; j++)
		{
			int randomNode = randInt(numNodes);
			randomWeight = randInt(maxWeight);
			//Make sure this edge is unique, if it isn't just omit the edge
			if (!edgeExists(edges[i], i, randomNode) && !edgeExists(edges[randomNode], randomNode, i))
			{
				edges[i].push_back(DirectedWeightedEdge(randomWeight, i, randomNode));
				edges[randomNode].push_back(DirectedWeightedEdge(randomWeight, randomNode, i));
			}
		}
	}
	return DirectedGraph(edges);
}

//This represents a few locations in my home town and the time in minutes to reach them according to Google Maps
//Not every node is connected to every other, but each node is connected to nodes that seem like reasonable destinations
DirectedGraph DirectedGraph::generateHandmadeGraph()
{
	std::map<int, std::vector<DirectedWeightedEdge>> edges;
	const int numNodes = 17;
	
	//initialize map with empty vectors
	for (int i = 0; i < numNodes; i++)
	{
		edges[i] = std::vector<DirectedWeightedEdge>();
	}
	
	edges[0].push_back(DirectedWeightedEdge(3, 0, 1));
	edges[0].push_back(DirectedWeightedEdge(1, 0, 3));
	edges[1].push_back(DirectedWeightedEdge(3, 1, 0));
	edges[1].push_back(DirectedWeightedEdge(4, 1, 2));
	edges[1].push_back(DirectedWeightedEdge(4, 1, 4));
	edges[2].push_back(DirectedWeightedEdge(4, 2, 1));
	edges[2].push_back(DirectedWeightedEdge(6, 2, 4));
	edges[3].push_back(DirectedWeightedEdge(1, 3, 0));
	edges[3].push_back(DirectedWeightedEdge(4, 3, 4));
	edges[3].push_back(DirectedWeightedEdge(8, 3, 10));
	edges[3].push_back(DirectedWeightedEdge(8, 3, 16));
	edges[4].push_back(DirectedWeightedEdge(4, 4, 1));
	edges[4].push_back(DirectedWeightedEdge(6, 4, 2));
	edges[4].push_back(DirectedWeightedEdge(4, 4, 3));
	edges[4].push_back(DirectedWeightedEdge(4, 4, 5));
	edges[4].push_back(DirectedWeightedEdge(8, 4, 9));
	edges[5].push_back(DirectedWeightedEdge(4, 5, 4));
	edges[5].push_back(DirectedWeightedEdge(4, 5, 6));
	edges[6].push_back(DirectedWeightedEdge(4, 6, 5));
	edges[6].push_back(DirectedWeightedEdge(3, 6, 7));
	edges[7].push_back(DirectedWeightedEdge(3, 7, 6));
	edges[7].push_back(DirectedWeightedEdge(4, 7, 8));
	edges[7].push_back(DirectedWeightedEdge(3, 7, 11));
	edges[8].push_back(DirectedWeightedEdge(4, 8, 7));
	edges[9].push_back(DirectedWeightedEdge(8, 9, 4));
	edges[9].push_back(DirectedWeightedEdge(5, 9, 10));
	edges[9].push_back(DirectedWeightedEdge(6, 9, 11));
	edges[9].push_back(DirectedWeightedEdge(7, 9, 15));
	edges[9].push_back(DirectedWeightedEdge(6, 9, 16));
	edges[10].push_back(DirectedWeightedEdge(8, 10, 3));
	edges[10].push_back(DirectedWeightedEdge(5, 10, 9));
	edges[10].push_back(DirectedWeightedEdge(7, 10, 12));
	edges[10].push_back(DirectedWeightedEdge(7, 10, 14));
	edges[11].push_back(DirectedWeightedEdge(3, 11, 7));
	edges[11].push_back(DirectedWeightedEdge(6, 11, 9));
	edges[11].push_back(DirectedWeightedEdge(8, 11, 12));
	edges[12].push_back(DirectedWeightedEdge(7, 12, 10));
	edges[12].push_back(DirectedWeightedEdge(8, 12, 11));
	edges[12].push_back(DirectedWeightedEdge(6, 12, 13));
	edges[13].push_back(DirectedWeightedEdge(6, 13, 12));
	edges[13].push_back(DirectedWeightedEdge(5, 13, 14));
	edges[14].push_back(DirectedWeightedEdge(7, 14, 10));
	edges[14].push_back(DirectedWeightedEdge(5, 14, 13));
	edges[14].push_back(DirectedWeightedEdge(5, 14, 15));
	edges[15].push_back(DirectedWeightedEdge(7, 15, 9));
	edges[15].push_back(DirectedWeightedEdge(5, 15, 14));
	edges[15].push_back(DirectedWeightedEdge(8, 15, 16));
	edges[16].push_back(DirectedWeightedEdge(8, 16, 3));
	edges[16].push_back(DirectedWeightedEdge(6, 16, 9));
	edges[16].push_back(DirectedWeightedEdge(8, 16, 15));

	return DirectedGraph(edges);
}
