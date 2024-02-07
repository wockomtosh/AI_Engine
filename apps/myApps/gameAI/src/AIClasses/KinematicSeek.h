#pragma once
#include "../Components/Rigidbody.h"

class KinematicSeek {

public:
	Rigidbody* body;

	Vector2 target1 = Vector2(80, 80);
	Vector2 target2 = Vector2(900, 80);
	Vector2 target3 = Vector2(900, 700);
	Vector2 target4 = Vector2(80, 700);
	Vector2 curTarget = target1;

	KinematicSeek(Rigidbody* body);
	void updateRigidbody(float dt);

};