#pragma once
#include "Action.h"
#include "Blackboard.h"
#include "../Components/AIComponent.h"
#include "DynamicEvade.h"

class EvadeNearestAction : public Action {
	Blackboard* blackboard;
	AIComponent* self;

public:
	EvadeNearestAction(Blackboard* blackboard, AIComponent* self);
	bool canInterrupt();
	virtual bool canDoBoth(Action* other);
	void execute();
};