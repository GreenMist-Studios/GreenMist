#ifndef VECTOR2_H
#define VECTOR2_H

#include <math.h>

class Vector2
{
public:
	Vector2();
	Vector2(float x, float y);
	Vector2(float i);
	~Vector2(void);

	static Vector2 One;
	static Vector2 Zero;

	int Length();
	void Add(Vector2* v);

	float X;
	float Y;

	Vector2 operator+(const Vector2& other);
	Vector2 operator-(const Vector2& other);
	Vector2 operator*(const float other);
	Vector2 operator/(const float other);
	void operator+=(const Vector2& other);
	void operator-=(const Vector2& other);
	void operator*=(const float other);
	void operator/=(const float other);
};

#endif
