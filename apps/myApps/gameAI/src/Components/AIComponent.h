#pragma once
#include <string>
#include "Rigidbody.h"
#include "../AIClasses/ISteeringBehavior.h"

struct AIComponent {
	Rigidbody* body;
	float maxAccel = 20;
	float maxAngular = 300;
	//Probably refactor this to be a list or map of tags later. 
	//I'm not sure which one I want and I might want to handle that in the gameObect so I'm putting it off.
	std::string tag; 

	ISteeringBehavior* behavior; //maybe make this multiple behaviors and call them all?

	AIComponent(Rigidbody* body, float maxAccel = 20, float maxAngular = 300) :
		body(body), maxAccel(maxAccel), maxAngular(maxAngular), tag("") {
		behavior = nullptr;
	}

	inline void update(float dt) {
		Acceleration steering = behavior->getSteering();
		//Before I had something to clamp to maxAccel. Turns out it wasn't actually doing that, and it's better when it doesn't clamp to maxAccel. 
		//So maxAccel is not a limit to how much the body can accelerate, it's a value used as a starting point for how fast it should accelerate for some behaviors.
		body->update(dt, steering);
	}
};