#include "Pathfinder.h"
#include <iostream>

//nodeID will be -1 if the value isn't found
NodeRecord findInListByNode(std::vector<NodeRecord> list, int nodeID)
{
	for (NodeRecord node : list)
	{
		if (node.nodeID == nodeID)
		{
			return node;
		}
	}
	return NodeRecord(-1, DirectedWeightedEdge::NULL_EDGE, -1, -1);
}

//Wrapper for std::push_heap
void heapPush(std::vector<NodeRecord> &list, NodeRecord value)
{
	list.push_back(value);
	std::push_heap(list.begin(), list.end(), NodeRecord());
}

//Wrapper for std::pop_heap
NodeRecord heapPop(std::vector<NodeRecord> &list)
{
	std::pop_heap(list.begin(), list.end(), NodeRecord());
	NodeRecord returnValue = list.back();
	list.pop_back();

	return returnValue;
}

std::vector<DirectedWeightedEdge> Pathfinder::findPath(int start, int goal, DirectedGraph* graph, Heuristic* heuristic, bool printNodesVisited)
{
	if (heuristic == nullptr)
	{
		heuristic = new DijkstraHeuristic();
	}

	//Initialize fringe
	NodeRecord startRecord = NodeRecord(start, DirectedWeightedEdge::NULL_EDGE, 0, heuristic->estimate(start));
	//Turns out std::priority_queue id pretty useless for our needs, so we need to make a heap from a vector.
	std::vector<NodeRecord> openList;
	heapPush(openList, startRecord);

	//The order of closedList doesn't matter so much
	std::vector<NodeRecord> closedList;

	NodeRecord current;
	while (!openList.empty())
	{
		current = heapPop(openList);

		if (current.nodeID == goal)
		{
			break;
		}

		std::vector<DirectedWeightedEdge> outgoingEdges = graph->getOutgoingEdges(current.nodeID);

		//Generate unique children
		for (DirectedWeightedEdge edge : outgoingEdges)
		{
			int endNode = edge.sink;
			float g = current.costSoFar + edge.weight;
			float h = heuristic->estimate(endNode);

			//This check isn't needed if the heuristic is consistent becasue the cost by which the node is first expanded will be the cheapest
			NodeRecord endNodeRecord = findInListByNode(closedList, endNode);
			if (endNodeRecord.nodeID != -1)
			{
				if (endNodeRecord.costSoFar <= g)
				{
					//Worse duplicate, skip it.
					continue;
				}
				else
				{
					//If it's a better duplicate, then erase the one in the closed list
					closedList.erase(std::find(closedList.begin(), closedList.end(), endNodeRecord));
				}
			}

			endNodeRecord = findInListByNode(openList, endNode);
			if (endNodeRecord.nodeID != -1)
			{
				if (endNodeRecord.costSoFar <= g)
				{
					//Worse duplicate, skip it
					continue;
				}
				//Should I be erasing from the openList if we have a better option elsewhere?
				//When running through manually it seems that the algorithm still works, but we have to redo a bunch of nodes that we already did.
				//They get pruned here when they're redone, but we still generate them.
				//I think the tradeoff is whether or not it's more efficient to delete the node and have to resort the heap, or to just redo a few nodes.
				//Generating the path at the end might get messed up because we could have duplicate nodes in the closed list.
			}

			//If it's unique or a better duplicate, we want to insert it.
			//TODO: THIS DOESN'T MATCH ROGELIO'S PSEUDOCODE, DOES THIS ACTUALLY WORK?!?!? I think his pseudocode is a bit wrong, but I'm not positive on the changes to make.
			endNodeRecord = NodeRecord(endNode, edge, g, g + h);
			heapPush(openList, endNodeRecord);
		}

		//We might want to make sure it's a unique insert here?
		//Though with how my find algorithm works, as long as we visited the cheaper duplicate first then it will still give the correct path.
		closedList.push_back(current);
	}

	if (current.nodeID != goal)
	{
		//No solution
		return std::vector<DirectedWeightedEdge>();
	}
	else
	{
		//generate path
		std::vector<DirectedWeightedEdge> path;
		while (current.nodeID != start)
		{
			path.push_back(current.incomingEdge);
			current = findInListByNode(closedList, current.incomingEdge.source);
		}
		std::reverse(path.begin(), path.end());
		if (printNodesVisited)
		{
			std::cout << "Nodes Visited (closed list): " << closedList.size() << std::endl;
		}
		return path;
	}
}

bool NodeRecord::operator>(NodeRecord other)
{
	return heuristicEstimate > other.heuristicEstimate;
}

bool NodeRecord::operator<(NodeRecord other)
{
	return heuristicEstimate < other.heuristicEstimate;
}

bool NodeRecord::operator==(NodeRecord other)
{
	return nodeID == other.nodeID && incomingEdge == other.incomingEdge && costSoFar == other.costSoFar && heuristicEstimate == other.heuristicEstimate;
}

bool NodeRecord::operator()(const NodeRecord& a, const NodeRecord& b)
{
	return a.heuristicEstimate > b.heuristicEstimate;
}
