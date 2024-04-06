#pragma once
#include "Decision.h"

//These times need to be updated elsewhere
class WanderTimeDecision : public Decision {
	float* wanderTime;
	float* wanderMax;

public:
	WanderTimeDecision(float* wanderTime, float* wanderMax) :
		wanderTime(wanderTime), wanderMax(wanderMax) {}

	bool isTrue()
	{
		return wanderTime > wanderMax;
	}
};