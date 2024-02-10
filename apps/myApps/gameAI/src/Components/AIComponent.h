#pragma once
#include "Rigidbody.h"
#include "../AIClasses/ISteeringBehavior.h"

struct AIComponent {
	Rigidbody* body;
	float maxAccel = 20;
	float maxAngular = 300;

	ISteeringBehavior* behavior; //maybe make this multiple behaviors and call them all?

	AIComponent(Rigidbody* body, float maxAccel = 20, float maxAngular = 300) :
		body(body), maxAccel(maxAccel), maxAngular(maxAngular) {
		behavior = nullptr;
	}

	inline void update(float dt) {
		//Clamp to max accel
		//TODO clamp max angular? The vector already clamps pos and neg (magnitude is always pos, vector direction is preserved), but for angular I'll need to watch out.
		if (behavior->getSteering().linear.getMagnitude() > maxAccel) {
			behavior->getSteering().linear = behavior->getSteering().linear.getVectorWithMagnitude(maxAccel);
		}
		body->update(dt, behavior->getSteering());
	}
};