#pragma once
#include "Rigidbody.h"
#include "../AIClasses/ISteeringBehavior.h"

struct AIComponent {
	Rigidbody* body;
	ISteeringBehavior* behavior; //maybe make this multiple behaviors and call them all?
	float maxAccel = 20;
	float maxAngular = 300;

	inline void update(float dt) {
		//Clamp to max accel
		//TODO clamp pos and neg?
		if (behavior->getSteering().linear.getMagnitude() > maxAccel) {
			behavior->getSteering().linear = behavior->getSteering().linear.getVectorWithMagnitude(maxAccel);
		}
		body->update(dt, behavior->getSteering());
	}
};