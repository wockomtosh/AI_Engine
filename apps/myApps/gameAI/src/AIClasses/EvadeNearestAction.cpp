#include "EvadeNearestAction.h"
#include <vector>
#include "../Components/AxisAlignedBoundingBox.h"

EvadeNearestAction::EvadeNearestAction(Blackboard* blackboard, AIComponent* self) :
	blackboard(blackboard), self(self)
{
	priority = 10;
	type = "movement";
}

bool EvadeNearestAction::canInterrupt()
{
	return true;
}

bool EvadeNearestAction::canDoBoth(Action* other)
{
	return other->type != "movement";
}

void EvadeNearestAction::execute()
{
	std::vector<AABB*> obstacles = *static_cast<std::vector<AABB*>*>(blackboard->getGeneric("obstacles"));

	AABB* closest = nullptr;
	for (AABB* obstacle : obstacles)
	{
		//I'm not wanting to really check for the closest so I'll just get the first one we overlap with
		//We only use this action if we're overlapping so this should work for now
		if (obstacle->isPointWithinBox(self->body->position))
		{
			closest = obstacle;
			break;
		}
	}

	//null check to be safe
	if (closest == nullptr)
	{
		//Do nothing if we aren't actually overlapping.
		return;
	}
	
	delete self->behavior;
	self->behavior = new DynamicEvade(self, closest->center, 300, 10);
}
