#pragma once
#include <ofMain.h>
#include "../Components/Rigidbody.h"
#include "../Components/AxisAlignedBoundingBox.h"

namespace Renderer {
	void draw(ofImage sprite, Rigidbody* body);
	void drawAABB(ofImage sprite, AABB* box);
};