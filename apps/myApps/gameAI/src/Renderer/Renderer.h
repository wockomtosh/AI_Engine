#pragma once
#include <ofMain.h>
#include "../DataTypes/Rigidbody.h"

class Renderer {
public:
	static void drawRigidbody(ofImage sprite, Rigidbody* body);
};