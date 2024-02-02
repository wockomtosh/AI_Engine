#pragma once

//Roughly equivalent of my Point2D class. Vector2 seems like a better name since a vector can describe a point or other things as well.
//I can also add some functions like getMagnitude
//Should I be inlining basically all of these functions?
class Vector2
{
	

public:
	float x;
	float y;

	Vector2();
	Vector2(float i_x, float i_y);

	float getX();
	float getY();
	void setX(float i_x);
	void setY(float i_y);

	float getMagnitude() const;
	Vector2 normalize() const;
	Vector2 getVectorWithMagnitude(float magnitude) const;
	bool isWithinRangeOf(Vector2 target, float xrange, float yrange) const;

	void print();
	
	Vector2 operator+=(Vector2 other);
	Vector2 operator-=(Vector2 other);
	Vector2 operator*=(Vector2 other);
	Vector2 operator/=(Vector2 other);
	Vector2 operator*=(float other);
	Vector2 operator/=(float other);
	Vector2 operator-();
	bool operator!=(Vector2 other);
	bool operator==(Vector2 other);

	~Vector2() {}

	static const Vector2 Up;
	static const Vector2 Down;
	static const Vector2 Left;
	static const Vector2 Right;
};

Vector2 operator+(Vector2 lhs, Vector2 rhs);
Vector2 operator-(Vector2 lhs, Vector2 rhs);
Vector2 operator*(Vector2 lhs, Vector2 rhs);
Vector2 operator/(Vector2 lhs, Vector2 rhs);
Vector2 operator*(Vector2 lhs, float rhs);
Vector2 operator*(float lhs, Vector2 rhs);
Vector2 operator/(Vector2 lhs, float rhs);