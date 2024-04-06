#pragma once
#include "Decision.h"
#include "../Components/Rigidbody.h"

//Whether or not a body is moving. Vector decisions like this could probably be abstracted into their own class but I'll worry about that later.
class IsMovingDecision : public Decision {
	Rigidbody* body;

public:
	IsMovingDecision(Rigidbody* body) :
		body(body) {}

	bool isTrue()
	{
		return body->velocity.getMagnitude() > 1;
	}
};