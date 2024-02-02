#pragma once

#include "../DataTypes/Rigidbody.h"

class AISystem {
	Rigidbody** rigidbodies = nullptr;
	int numRigidbodies = 0;


public:
	AISystem(Rigidbody** rigidbodies, int numRigidbodies);

	void update();
};