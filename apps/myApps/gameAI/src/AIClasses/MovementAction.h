#pragma once
#include "Action.h"
#include "ISteeringBehavior.h"

class MovementAction : public Action {
	ISteeringBehavior* movement;

public:
	MovementAction(ISteeringBehavior* movement);
};