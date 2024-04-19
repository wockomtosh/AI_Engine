#pragma once
#include "Action.h"
#include "Blackboard.h"
#include "../Components/Rigidbody.h"
#include "../Components/AIComponent.h"
#include "DynamicSeek.h"

class ChaseTargetAction : public Action {
	Blackboard* blackboard;
	AIComponent* self;
	Rigidbody* target;

public:
	ChaseTargetAction(Blackboard* blackboard, AIComponent* self, Rigidbody* target) :
		blackboard(blackboard), self(self), target(target)
	{
		priority = 2;
		type = "movement";
	}

	void execute()
	{
		delete self->behavior;
		self->behavior = new DynamicSeek(target->position, self);
	}

	bool canDoBoth(Action* other) { return other->type != "movement"; }

	bool canInterrupt() { return true; };
};