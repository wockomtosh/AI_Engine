#pragma once
#include "Action.h"
#include "Blackboard.h"
#include "../DataTypes/Status.h"
#include "../Components/AIComponent.h"
#include "DynamicPathfollow.h"
#include "Pathfinding/ManhattanHeuristic.h"
#include "Pathfinding/Pathfinder.h"
#include <iostream>

//This action is a continuous pathfinding action. It uses the Status enum to track its completion
class PathfindAction : public Action {
	AIComponent* self;
	Vector2 target;
	TileGraph* graph;
	Status status = Status::none;
	std::vector<DirectedWeightedEdge> path;

public:
	PathfindAction(AIComponent* self, Vector2 target, TileGraph* graph) :
		self(self), target(target), graph(graph)
	{
		priority = 1;
		type = "movement";
	}

	bool canInterrupt() { return true; }

	bool canDoBoth(Action* other) { return other->type != "movement"; }

	bool isComplete() { return (status == Status::success || status == Status::failure); }

	bool isSuccessful() { return status == Status::success; }

	void execute()
	{
		if (status == Status::none)
		{
			int startNode = graph->getNodeFromWorldCoordinate(self->body->position.x, self->body->position.y);
			int endNode = graph->getNodeFromWorldCoordinate(target.x, target.y);

			if (!graph->checkIsNodeValid(endNode))
			{
				std::cout << "ERROR IN PATHFIND ACTION TARGET" << std::endl;
				return;
			}

			path = Pathfinder::findPath(startNode, endNode, graph, new ManhattanHeuristic(endNode, graph));

			delete self->behavior;
			self->behavior = new DynamicPathfollow(self, graph, path, 32, 32);

			status = Status::running;
		}

		if (status == Status::running)
		{
			bool isAtTargetLocation = self->body->position.isWithinRangeOf(target, 40, 40);
			if (isAtTargetLocation)
			{
				status = Status::success;
			}

			//It failed if we don't have a path.
			if (path.size() == 0)
			{
				status = Status::failure;
			}
		}
	}

	void reset() 
	{
		status = Status::none;
	}
};