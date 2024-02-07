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

Vector2 operator-(Vector2 lhs, Vector2 rhs)
{
	return Vector2(lhs.getX() - rhs.getX(), lhs.getY() - rhs.getY());
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

const Vector2 Vector2::Up = Vector2(0.0, 1.0);
const Vector2 Vector2::Down = Vector2(0.0, -1.0);
const Vector2 Vector2::Left = Vector2(-1.0, 0.0);
const Vector2 Vector2::Right = Vector2(1.0, 0.0);
const Vector2 Vector2::NULL_VECTOR = Vector2(-10000, -10000);