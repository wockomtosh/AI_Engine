#pragma once
#include "Condition.h"

class PlayerIsAliveCondition : public Condition {

public:

	bool isTrue(Blackboard* blackboard)
	{
		return blackboard->getBool("playerIsAlive");
	}
};