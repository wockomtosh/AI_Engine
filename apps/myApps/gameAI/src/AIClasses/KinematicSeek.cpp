#include "KinematicSeek.h"

KinematicSeek::KinematicSeek(Rigidbody* body) :
	body(body)
{
}

void KinematicSeek::updateRigidbody(float dt)
{
	Vector2 directionToTarget = curTarget - body->position;
	Vector2 velocity = directionToTarget.getVectorWithMagnitude(body->maxSpeed);
	body->velocity = velocity;
	body->update(dt, {Vector2(), 0});

	if (body->position.isWithinRangeOf(target1, 1, 1)) {
		curTarget = target2;
	}
	if (body->position.isWithinRangeOf(target2, 1, 1)) {
		curTarget = target3;
	}
	if (body->position.isWithinRangeOf(target3, 1, 1)) {
		curTarget = target4;
	}
}
