#include "Rigidbody.h"
#include <corecrt_math.h>
#include <iostream>

//TODO: should this be a public static function somewhere?
//If I want to get crazy with it I could make an orientation type that does this automatically...
float clampOrientation(float i_orientation)
{
	//I'm using degrees
	if (i_orientation < 0)
	{
		i_orientation += 360;
	}
	else if (i_orientation > 360)
	{
		i_orientation -= 360;
	}

	return i_orientation;
}

void Rigidbody::update(float dt, Acceleration acceleration) {

	velocity += dt * acceleration.linear;
	rotation += dt * acceleration.angular;

	//Clamp to max speed and rotation
	if (rotation > maxRotation)
	{
		rotation = maxRotation;
	}
	if (rotation < -maxRotation)
	{
		rotation = -maxRotation;
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

	orientation = clampOrientation(orientation);
}

//TODO: Should this be in LookWhereYouAreGoing?
float Rigidbody::getOrientationOfMovement()
{
	float oMovement = atan2(velocity.y, velocity.x) * (180 / 3.1415);
	//This function gives 0 orientation as pointing to the right, so we need to offset that properly.
	oMovement += 90;

	oMovement = clampOrientation(oMovement);

	return oMovement;
}