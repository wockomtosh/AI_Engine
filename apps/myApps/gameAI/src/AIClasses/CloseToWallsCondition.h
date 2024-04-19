#pragma once
#include "Condition.h"
#include "../Components/AxisAlignedBoundingBox.h"
#include "../Components/Rigidbody.h"
#include <vector>

class CloseToWallsCondition : public Condition {

public:

	bool isTrue(Blackboard* blackboard)
	{
		std::vector<AABB*> obstacles = *static_cast<std::vector<AABB*>*>(blackboard->getGeneric("obstacles"));
		Rigidbody* self = static_cast<Rigidbody*>(blackboard->getGeneric("monster"));

		bool tooClose = false;
		for (AABB* obstacle : obstacles)
		{
			//I'm doing this assuming that my extents are expanded to account for the boid's area.
			if (obstacle->isPointWithinBox(self->position.x, self->position.y))
			{
				tooClose = true;
				break;
			}
		}
		return tooClose;
	}
};