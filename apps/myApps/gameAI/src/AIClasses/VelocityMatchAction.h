#pragma once
#include "Action.h"
#include "Blackboard.h"
#include "../Components/AIComponent.h"
#include "DynamicVelocityMatch.h"

class VelocityMatchAction : public Action {
	AIComponent* self;
	Rigidbody* target;

public:
	VelocityMatchAction(AIComponent* self, Rigidbody* target) :
		self(self), target(target)
	{
		priority = 1;
		type = "movement";
	}

	bool canDoBoth(Action* other) { return other->type != "movement"; }

	void execute()
	{
		delete self->behavior;
		self->behavior = new DynamicVelocityMatch(self, target->velocity);
	}
};