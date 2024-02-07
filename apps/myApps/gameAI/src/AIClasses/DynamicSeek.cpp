#include "DynamicSeek.h"

DynamicSeek::DynamicSeek(Vector2 target, AIComponent* self) :
	target(target), self(self)
{
}

DynamicSeek::~DynamicSeek()
{
	//DON'T delete the AIComponent because if we want to update our target we need a new DynamicSeek
	//Is this behavior pattern good? Idk, but we'll see.
}

Acceleration DynamicSeek::getSteering()
{
	//TODO orient in the direction of travel
	Vector2 seekVector = target - self->body->position;
	seekVector *= self->maxAccel;
	return Acceleration(seekVector, 0);
}
