#pragma once
#include "ISteeringBehavior.h"
#include "../Components/AIComponent.h"

class DynamicSeek : public ISteeringBehavior {
	Vector2 target;
	AIComponent* self;
	bool lookWhereYouAreGoing;

public:
	DynamicSeek(Vector2 target, AIComponent* self, bool lookWhereYouAreGoing = true);
	~DynamicSeek();
	Acceleration getSteering();
};