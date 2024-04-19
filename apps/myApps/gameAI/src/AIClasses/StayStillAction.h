#pragma once
#include "Action.h"
#include "Blackboard.h"
#include "../Components/AIComponent.h"
#include "DynamicVelocityMatch.h"

class StayStillAction : public Action {
	AIComponent* self;

public:
	StayStillAction(AIComponent* self) :
		self(self)
	{
		priority = 1;
		type = "movement";
	}

	bool canDoBoth(Action* other) { return other->type != "movement"; }

	bool isComplete() { return true; }

	void execute()
	{
		delete self->behavior;
		self->behavior = new DynamicVelocityMatch(self, Vector2());
	}
};