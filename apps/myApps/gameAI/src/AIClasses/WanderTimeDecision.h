#pragma once
#include "Decision.h"

//These times need to be updated elsewhere
class WanderTimeDecision : public Decision {
	Blackboard* blackboard;
	float wanderMax;

public:
	WanderTimeDecision(Blackboard* blackboard, float wanderMax) :
		blackboard(blackboard), wanderMax(wanderMax) {}

	bool isTrue()
	{
		return blackboard->getFloat("wanderTime") > wanderMax;
	}
};