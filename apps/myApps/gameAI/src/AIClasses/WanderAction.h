#pragma once
#include "Action.h"
#include "Blackboard.h"
#include "../Components/AIComponent.h"
#include "DynamicWander.h"

class WanderAction : public Action {
	AIComponent* self;

public:
	WanderAction(AIComponent* self) :
		self(self) 
	{
		priority = 1;
		type = "movement";
	}

	virtual bool canDoBoth(Action* other) { return other->type != "movement"; }

	void execute()
	{
		delete self->behavior;
		self->behavior = new DynamicWander(self);
	}
};