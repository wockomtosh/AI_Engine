#include "TileGraph.h"

TileGraph::TileGraph(int tileSize, int maxX, int maxY, std::vector<AABB*> obstacles) :
	tileSize(tileSize), maxX(maxX), maxY(maxY)
{
	//Right now I'm making the intentional choice to not connect the edges of the tile graph to each other

	findValidNodes(obstacles);
	setupEdges();
}

void TileGraph::findValidNodes(std::vector<AABB*> obstacles)
{
	int nodeMaxX = maxX / tileSize;
	int nodeMaxY = maxY / tileSize;

	//TODO: Nodes are valid by default, we could probably do this by iterating through obstacles and marking all nodes they overlap as invalid
	//However, that seems harder to implement so that's for later

	//Iterate through each possible node to check for validity. If the center is occupied, the whole node is invalid. It will have no outgoing edges
	std::map<int, bool> isNodeValidSetup;

	for (int x = 0; x < nodeMaxX; x++)
	{
		for (int y = 0; y < nodeMaxY; y++)
		{
			int node = getNodeIndexFromNodeCoordinate(x, y);
			Vector2 nodeCenter = getWorldCoordinateFromNodeCoordinate(x, y);
			bool isValid = true;
			for (auto obstacle : obstacles)
			{
				if (obstacle->isPointWithinBox(nodeCenter.x, nodeCenter.y))
				{
					isValid = false;
					break;
				}
			}
			isNodeValidSetup[node] = isValid;
		}
	}

	isNodeValid = isNodeValidSetup;
}

void TileGraph::setupEdges()
{
	int nodeMaxX = maxX / tileSize;
	int nodeMaxY = maxY / tileSize;

	std::map<int, std::vector<DirectedWeightedEdge>> tileGraphEdges;
	for (int x = 0; x < nodeMaxX; x++)
	{
		for (int y = 0; y < nodeMaxY; y++)
		{
			int node = getNodeIndexFromNodeCoordinate(x, y);
			std::vector<DirectedWeightedEdge> nodeEdges;
			//We only need to get edges for valid nodes
			if (isNodeValid[node])
			{
				//Check each of the 4 cardinal directions for validity and set up an edge there.
				//Make sure that we are handling the edges properly. For now I'm ignoring them.
				if (x > 0)
				{
					int westNode = getNodeIndexFromNodeCoordinate(x - 1, y);
					if (isNodeValid[westNode])
					{
						//In our tile graph all weights are 1, since all of these edges are adjacent to each other.
						nodeEdges.push_back(DirectedWeightedEdge(1, node, westNode));
					}
				}
				if (y > 0)
				{
					int northNode = getNodeIndexFromNodeCoordinate(x, y - 1);
					if (isNodeValid[northNode])
					{
						nodeEdges.push_back(DirectedWeightedEdge(1, node, northNode));
					}
				}
				if (x != nodeMaxX - 1)
				{
					int eastNode = getNodeIndexFromNodeCoordinate(x + 1, y);
					if (isNodeValid[eastNode])
					{
						nodeEdges.push_back(DirectedWeightedEdge(1, node, eastNode));
					}
				}
				if (y != nodeMaxY - 1)
				{
					int southNode = getNodeIndexFromNodeCoordinate(x, y + 1);
					if (isNodeValid[southNode])
					{
						nodeEdges.push_back(DirectedWeightedEdge(1, node, southNode));
					}
				}
			}
			tileGraphEdges[node] = nodeEdges;
		}
	}
	edges = tileGraphEdges;
}

int TileGraph::getNodeIndexFromNodeCoordinate(int x, int y)
{
	//This only works if it is 0-indexed
	return x + (y * maxX);
}

int TileGraph::getNodeFromWorldCoordinate(float x, float y)
{
	//Map the world coordinate to a node coordinate
	int nodeX = x / tileSize;
	int nodeY = y / tileSize;
	//Then map the node coordinate to a node index
	return getNodeIndexFromNodeCoordinate(nodeX, nodeY);
}

Vector2 TileGraph::getNodeCoordinateFromNode(int node)
{
	return Vector2(node % maxX, node / maxX);
}

Vector2 TileGraph::getWorldCoordinateFromNodeCoordinate(int x, int y)
{
	//Multiply by tileSize and add tileSize/2 to go to the center of the tile in world coordinates
	float worldX = (x * tileSize) + static_cast<float>((tileSize / 2));
	float worldY = (y * tileSize) + static_cast<float>((tileSize / 2));
	return Vector2(worldX, worldY);
}

Vector2 TileGraph::getWorldCoordinateFromNode(int node)
{
	//Convert the node to node coordinates
	int nodeX = node % maxX;
	int nodeY = node / maxX;
	//Convert node coordinates to world coordinates
	return getWorldCoordinateFromNodeCoordinate(nodeX, nodeY);
}

bool TileGraph::checkIsNodeValid(int node)
{
	return isNodeValid[node];
}