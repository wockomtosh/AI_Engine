#pragma once
#include "Rigidbody.h"
#include "../AIClasses/ISteeringBehavior.h"

struct AIComponent {
	Rigidbody* body;
	ISteeringBehavior* behavior;

	inline void update(float dt) {
		body->update(dt, behavior->getSteering());
	}
};