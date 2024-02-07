#pragma once
#include "../DataTypes/Vector2.h"

//Where do these variables belong? It makes sense to have them in ofApp.h,
//but it makes sense to clamp position in the rigidbody
static const int WINDOW_WIDTH = 1024;
static const int WINDOW_HEIGHT = 768;

struct Acceleration {
	Vector2 linear;
	float angular;
	Acceleration(Vector2 linear, float angular) : linear(linear), angular(angular) {}
};

struct Rigidbody {
	Vector2 position = Vector2();
	float orientation = 0;
	Vector2 velocity = Vector2();
	float rotation = 0;
	float maxSpeed = 100;
	float maxRotation = 100;

	~Rigidbody() {}

	void update(float dt, Acceleration acceleration);
	float getOrientationOfMovement();
};