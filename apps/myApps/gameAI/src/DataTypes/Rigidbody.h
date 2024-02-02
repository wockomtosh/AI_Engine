#pragma once
#include "Vector2.h"

//Where do these variables belong? It makes sense to have them in ofApp.h,
//but it makes sense to clamp position in the rigidbody
static const int WINDOW_WIDTH = 1024;
static const int WINDOW_HEIGHT = 768;

struct SteeringOutput {
	//accelerations
	Vector2 linear;
	float angular;
};

struct Rigidbody {
	Vector2 position = Vector2();
	float orientation = 0;
	Vector2 velocity = Vector2();
	float rotation = 0;
	float maxSpeed = 100;
	float maxRotation = 100;

	void update(float dt, SteeringOutput steering) {
		//Should I be clamping acceleration here or elsewhere?
		//Or do I need to clamp it at all if I'm clamping speed?

		velocity += dt * steering.linear;
		rotation += dt * steering.angular;

		//Clamp to max speed and rotation
		if (rotation > maxRotation)
		{
			rotation = maxRotation;
		}
		if (velocity.getMagnitude() > maxSpeed)
		{
			velocity = velocity.getVectorWithMagnitude(maxSpeed);
		}

		position += dt * velocity;
		orientation += dt * rotation;

		//Implement wraparound
		if (position.x > WINDOW_WIDTH)
		{
			position.x = 0;
		}
		else if (position.x < 0)
		{
			position.x = WINDOW_WIDTH;
		}
		if (position.y > WINDOW_HEIGHT)
		{
			position.y = 0;
		}
		else if (position.y < 0)
		{
			position.y = WINDOW_HEIGHT;
		}

		//Clamp orientation. I'm using degrees
		if (orientation < 0)
		{
			orientation += 360;
		}
		else if (orientation > 360)
		{
			orientation -= 360;
		}
	}

	float getOrientationOfMovement() {

	}
};