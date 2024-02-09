#include "DynamicSeek.h"
#include <math.h>
#include "DynamicAlign.h"

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
	float angular = DynamicAlign::lookWhereYouAreGoing(self, 20, 2, .1);
	Vector2 seekVector = target - self->body->position;
	seekVector *= self->maxAccel;
	return Acceleration(seekVector, angular);
}
