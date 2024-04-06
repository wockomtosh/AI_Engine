#pragma once
#include <vector>
#include "Decision.h"
#include "../Components/Rigidbody.h"
#include "../Components/AxisAlignedBoundingBox.h"

//Should probably generalize the AABBs into points or bodies or something. I'll do that later.
//I really need a GameObject that holds the location so I can not worry about what 'type' of object it is.
class TooCloseDecision : public Decision {
	Blackboard* blackboard;
	Rigidbody* body;

public:
	TooCloseDecision(Blackboard* blackboard, Rigidbody* body) :
		blackboard(blackboard), body(body) {}

	bool isTrue()
	{
		std::vector<AABB*> obstacles = *static_cast<std::vector<AABB*>*>(blackboard->getGeneric("obstacles"));

		bool tooClose = false;
		for (AABB* obstacle : obstacles)
		{
			//I'm doing this assuming that my extents are expanded to account for the boid's area.
			if (obstacle->isPointWithinBox(body->position.x, body->position.y))
			{
				tooClose = true;
				break;
			}
		}
		return tooClose;
	}
};