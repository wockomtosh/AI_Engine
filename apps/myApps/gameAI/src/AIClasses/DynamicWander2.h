#pragma once
#include "ISteeringBehavior.h"
#include "../Components/AIComponent.h"
#include "DynamicSeek.h"

class DynamicWander2 : public ISteeringBehavior {
	AIComponent* self;
	float wanderOffset;

	DynamicSeek* seek;

public:
	DynamicWander2(AIComponent* self, float wanderOffset = 5);
	~DynamicWander2();
	Acceleration getSteering();
};