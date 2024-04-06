#pragma once
#include "Action.h"
#include "Blackboard.h"
#include "../Components/AIComponent.h"
#include "DynamicPathfollow.h"
#include "Pathfinding/ManhattanHeuristic.h"
#include "Pathfinding/Pathfinder.h"

class PathfindHomeAction : public Action {
	AIComponent* self;
	TileGraph* graph;
	std::vector<DirectedWeightedEdge> path;

public:
	PathfindHomeAction(AIComponent* self, TileGraph* graph) :
		self(self), graph(graph)
	{
		priority = 1;
		type = "movement";
	}

	virtual bool canDoBoth(Action* other) { return other->type != "movement"; }

	void execute()
	{
		if (self->behavior->getName() != "DynamicPathfollow")
		{
			int startNode = graph->getNodeFromWorldCoordinate(self->body->position.x, self->body->position.y);
			int endNode = graph->getNodeFromWorldCoordinate(80, 700);

			if (!graph->checkIsNodeValid(endNode))
			{
				return;
			}

			path = Pathfinder::findPath(startNode, endNode, graph, new ManhattanHeuristic(endNode, graph));

			delete self->behavior;
			self->behavior = new DynamicPathfollow(self, graph, path, 64, 32);
		}
	}
};