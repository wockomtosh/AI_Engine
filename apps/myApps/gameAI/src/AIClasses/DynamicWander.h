#pragma once
#include "ISteeringBehavior.h"
#include "../Components/AIComponent.h"
#include "DynamicSeek.h"

class DynamicWander : public ISteeringBehavior {
	AIComponent* self;
	float wanderOffset;
	float wanderRadius;
	float wanderRate;

	DynamicSeek* seek;

public:
	/*
	* WanderRadius > WanderOffset makes it turn around more
	* To get the target it rotates a vector on the WanderRadius around a point at distance WanderOffset from the boid.
	* The wanderRate roughly equates to the max degrees that it can rotate the wander target either direction (Capped at 90 then?)
	*/
	DynamicWander(AIComponent* self, float wanderOffset = 5, float wanderRadius = 6, float wanderRate = 100);
	~DynamicWander();
	Acceleration getSteering();
};