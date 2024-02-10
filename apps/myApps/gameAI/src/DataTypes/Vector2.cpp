#include <iostream>
#include "Vector2.h"


Vector2::Vector2()
{
	x = 0;
	y = 0;
}

Vector2::Vector2(float i_x, float i_y)
{
	x = i_x;
	y = i_y;
}

float Vector2::getX() { return x; }
float Vector2::getY() { return y; }

void Vector2::setX(float i_x) { x = i_x; }
void Vector2::setY(float i_y) { y = i_y; }

float Vector2::getMagnitude() const
{
	return sqrt(pow(x, 2) + pow(y, 2));
}

Vector2 Vector2::normalize() const
{
	float magnitude = getMagnitude();
	if (magnitude != 0) 
	{
		return Vector2(x, y) / getMagnitude();
	}
	return Vector2(0, 0);
}

Vector2 Vector2::getVectorWithMagnitude(float magnitude) const
{
	return normalize() * magnitude;
}

bool Vector2::isWithinRangeOf(Vector2 target, float xrange, float yrange) const
{
	bool withinXRange = x < (target.x + xrange) && x > (target.x - xrange);
	bool withinYRange = y < (target.y + yrange) && y >(target.y - yrange);
	return withinXRange && withinYRange;
}

Vector2 Vector2::rotateAroundPoint(Vector2 point, float angle, bool isDegrees) const
{
	/*
	* Rotation matrix is
	* [ cos -sin ]
	* [ sin cos  ]
	* Multiplied out (since I don't want to implement matrices right now) comes out to
	* (xcos - ysin, xsin + ycos)
	* To rotate around a point we translate to the origin, apply the rotation, and then translate back to our point
	*/

	float radians = angle;

	if (isDegrees)
	{
		radians *= (3.14159 / 180);
	}
	
	Vector2 translateToOrigin = Vector2(x - point.x, y - point.y);
	float xinter = cosf(radians);
	float yinter = sinf(radians);
	Vector2 rotate = Vector2((translateToOrigin.x * cosf(radians)) - (translateToOrigin.y * sinf(radians)), (translateToOrigin.x * sinf(radians)) + (translateToOrigin.y * cosf(radians)));
	Vector2 translateBack = Vector2(rotate.x + point.x, rotate.y + point.y);

	return translateBack;
}

void Vector2::print()
{
	std::cout << "[" << x << ", " << y << "]";
}

Vector2 Vector2::operator+=(Vector2 other)
{
	x += other.x;
	y += other.y;
	return Vector2(x, y);
}

Vector2 Vector2::operator-=(Vector2 other)
{
	x -= other.x;
	y -= other.y;
	return Vector2(x, y);
}

Vector2 Vector2::operator*=(Vector2 other)
{
	x *= other.x;
	y *= other.y;
	return Vector2(x, y);
}

Vector2 Vector2::operator/=(Vector2 other)
{
	x /= other.x;
	y /= other.y;
	return Vector2(x, y);
}

Vector2 Vector2::operator*=(float other)
{
	x *= other;
	y *= other;
	return Vector2(x, y);
}

Vector2 Vector2::operator/=(float other)
{
	x /= other;
	y /= other;
	return Vector2(x, y);
}

Vector2 Vector2::operator-()
{
	return Vector2(-x, -y);
}


bool Vector2::operator!=(Vector2 other)
{
	return (y != other.getX() && y != other.getY());
}

bool Vector2::operator==(Vector2 other)
{
	return (x == other.getX() && y == other.getY());
}



Vector2 operator+(Vector2 lhs, Vector2 rhs)
{
	return Vector2(lhs.getX() + rhs.getX(), lhs.getY() + rhs.getY());
}

Vector2 operator+(Vector2 lhs, float rhs)
{
	return Vector2(lhs.x + rhs, lhs.y + rhs);
}

Vector2 operator-(Vector2 lhs, Vector2 rhs)
{
	return Vector2(lhs.getX() - rhs.getX(), lhs.getY() - rhs.getY());
}

Vector2 operator-(Vector2 lhs, float rhs)
{
	return Vector2(lhs.x - rhs, lhs.y - rhs);
}

Vector2 operator*(Vector2 lhs, Vector2 rhs)
{
	return Vector2(lhs.getX() * rhs.getX(), lhs.getY() * rhs.getY());
}

Vector2 operator/(Vector2 lhs, Vector2 rhs)
{
	return Vector2(lhs.getX() / rhs.getX(), lhs.getY() / rhs.getY());
}

Vector2 operator*(Vector2 lhs, float rhs)
{
	return Vector2(lhs.getX() * rhs, lhs.getY() * rhs);
}

Vector2 operator*(float lhs, Vector2 rhs)
{
	return Vector2(lhs * rhs.getX(), lhs * rhs.getY());
}

Vector2 operator/(Vector2 lhs, float rhs)
{
	return Vector2(lhs.getX() / rhs, lhs.getY() / rhs);
}

Vector2 Vector2::getUnitVectorFromAngle(float degrees)
{
	//for cosf and sinf they assume 0 is pointing to the right, so we need to adjust
	float adjustedDegrees = degrees - 90;
	float radians = adjustedDegrees * 3.14159 / 180;
	//I'm flipping the sin() and cos() since that seems to be necessary
	return Vector2(cosf(radians), sinf(radians));
}

const Vector2 Vector2::Up = Vector2(0.0, 1.0);
const Vector2 Vector2::Down = Vector2(0.0, -1.0);
const Vector2 Vector2::Left = Vector2(-1.0, 0.0);
const Vector2 Vector2::Right = Vector2(1.0, 0.0);
const Vector2 Vector2::NULL_VECTOR = Vector2(-10000, -10000);