#pragma once
#include "../DataTypes/Vector2.h"

struct AABB {
	Vector2 center = Vector2();
	Vector2 extents = Vector2();

	AABB() {}
	AABB(Vector2 center, Vector2 extents) : center(center), extents(extents) {}
	~AABB() {}

	bool isPointWithinBox(float x, float y)
	{
		return !(x > center.x + extents.x || x < center.x - extents.x
			|| y > center.y + extents.y || y < center.y - extents.y);
	}
	bool isPointWithinBox(Vector2 point)
	{
		float x = point.x;
		float y = point.y;
		return !(x > center.x + extents.x || x < center.x - extents.x
			|| y > center.y + extents.y || y < center.y - extents.y);
	}
};