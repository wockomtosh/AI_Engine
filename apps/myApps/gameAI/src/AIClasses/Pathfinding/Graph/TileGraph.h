#pragma once
#include "DirectedGraph.h"
#include "../../../DataTypes/Vector2.h"
#include "../../../Components/AxisAlignedBoundingBox.h"

class TileGraph : public DirectedGraph {
private:
	int tileSize;
	int maxX;
	int maxY;
	std::map<int, bool> isNodeValid;

	void findValidNodes(std::vector<AABB*> obstacles);
	void setupEdges();

public:
	TileGraph(int tileSize, int maxX, int maxY, std::vector<AABB*> obstacles);
	~TileGraph() {}

	int getNodeIndexFromNodeCoordinate(int x, int y);
	int getNodeFromWorldCoordinate(float x, float y);
	Vector2 getNodeCoordinateFromNode(int node);
	Vector2 getWorldCoordinateFromNodeCoordinate(int x, int y);
	Vector2 getWorldCoordinateFromNode(int node);
	bool checkIsNodeValid(int node);
};