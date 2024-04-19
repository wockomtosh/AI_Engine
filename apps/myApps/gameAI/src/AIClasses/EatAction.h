#pragma once
#include "Action.h"
#include "Blackboard.h"
#include "../Components/Rigidbody.h"

class EatAction : public Action {
	Blackboard* blackboard;
	Rigidbody* target;

public:
	EatAction(Blackboard* blackboard, Rigidbody* target) :
		blackboard(blackboard), target(target)
	{
		priority = 3;
		type = "attack";
	}

	void execute()
	{
		target->maxSpeed = 0;
		target->maxRotation = 0;
		blackboard->setBool("playerIsAlive", false);
	}

	bool canInterrupt() { return true; };
};