#include "DynamicPathfollow.h"

DynamicPathfollow::DynamicPathfollow(AIComponent* self, TileGraph* graph, std::vector<DirectedWeightedEdge> path, float sinkRadius, float targetRadius, float timeToTargetVelocity) :
	self(self), graph(graph), path(path), sinkRadius(sinkRadius), targetRadius(targetRadius), timeToTargetVelocity(timeToTargetVelocity) {}

Acceleration DynamicPathfollow::getSteering()
{
	float angular = DynamicAlign::lookWhereYouAreGoing(self, 20, 2, .1);

	//Sometimes this crashes, I think it's when the path is being changed
	if (path.size() > 0)
	{
		Vector2 target = graph->getWorldCoordinateFromNode(path[pathIndex].sink);
		Vector2 targetVector = target - self->body->position;
		float distance = targetVector.getMagnitude();
		//If we made it to a node then we should immediately move to the next node
		if (distance < sinkRadius)
		{
			//Only move to the next node if we haven't made it to the end yet.
			if (pathIndex != path.size() - 1)
			{
				pathIndex++;
				target = graph->getWorldCoordinateFromNode(path[pathIndex].sink);
			}

		}

		return Acceleration(DynamicArrive::arrive(self, target, targetRadius, targetRadius, timeToTargetVelocity), angular);
	}
	return Acceleration(Vector2(), 0);
}
