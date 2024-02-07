#pragma once
#include "ISteeringBehavior.h"
#include "../Components/AIComponent.h"

class DynamicSeek : public ISteeringBehavior {
	Vector2 target;
	AIComponent* self;

public:
	DynamicSeek(Vector2 target, AIComponent* self);
	~DynamicSeek();
	Acceleration getSteering();
};