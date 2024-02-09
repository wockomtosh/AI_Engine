#pragma once
#include "ISteeringBehavior.h"
#include "../Components/AIComponent.h"

class DynamicAlign : public ISteeringBehavior {
	AIComponent* self;
	float target;
	float slowRadius;
	float targetRadius;
	float timeToTargetRotation;

public:
	DynamicAlign(AIComponent* self, float target);
	DynamicAlign(AIComponent* self, float target, float slowRadius, float targetRadius, float timeToTargetRotation);
	~DynamicAlign();
	Acceleration getSteering();

	//Basically a static version of getSteering that I want so I can combine this more easily with other movement behaviors. 
	//I might alter this later based on how my architecture changes, but for now this is what I'm doing.
	//Later I should maybe add the getMovementOrientation() into here
	static float lookWhereYouAreGoing(AIComponent* self, float slowRadius, float targetRadius, float timeToTargetRotation);

};