#include "Rigidbody.h"
#include <corecrt_math.h>

void Rigidbody::update(float dt, Acceleration acceleration) {

	velocity += dt * acceleration.linear;
	rotation += dt * acceleration.angular;

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

float Rigidbody::getOrientationOfMovement()
{
	return atan2(velocity.y, velocity.x) * (180 / 3.1415);
}
