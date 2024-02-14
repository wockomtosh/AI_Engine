#include "DynamicSeek.h"
#include <math.h>
#include "DynamicAlign.h"

DynamicSeek::DynamicSeek(Vector2 target, AIComponent* self, bool lookWhereYouAreGoing) :
	target(target), self(self), lookWhereYouAreGoing(lookWhereYouAreGoing)
{
}

DynamicSeek::~DynamicSeek()
{
	//DON'T delete the AIComponent because if we want to update our target we need a new DynamicSeek
	//Is this AI behavior pattern good? Idk, but we'll see.
}

Acceleration DynamicSeek::getSteering()
{
	float angular = 0;
	if (lookWhereYouAreGoing)
	{
		angular = DynamicAlign::lookWhereYouAreGoing(self, 20, 2, .1);
	}
	Vector2 seekVector = target - self->body->position;
	seekVector *= self->maxAccel;
	return Acceleration(seekVector, angular);
}

Vector2 DynamicSeek::seek(Vector2 target, AIComponent* self)
{
	Vector2 seekVector = target - self->body->position;
	seekVector *= self->maxAccel;
	return seekVector;
}
