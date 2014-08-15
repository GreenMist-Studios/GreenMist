#include "Vector2.h"

Vector2 Vector2::One = Vector2(1);
Vector2 Vector2::Zero = Vector2();

Vector2::Vector2(void)
{
	X = 0;
	Y = 0;
}

Vector2::Vector2(float i)
{
	X = i;
	Y = i;
}


Vector2::Vector2(float x, float y)
{
	X = x;
	Y = y;
}

Vector2::~Vector2(void)
{
	X = 0;
	Y = 0;
}

int Vector2::Length()
{
	return (int) sqrt(X*X + Y*Y);
}

Vector2 Vector2::operator+(const Vector2&  other)
{
	return Vector2( X+other.X, Y+other.Y );
}

Vector2 Vector2::operator-(const Vector2&  other)
{
	return Vector2( X-other.X, Y-other.Y );
}

Vector2 Vector2::operator*(const float other)
{
	return Vector2( X*other, Y*other);
}

Vector2 Vector2::operator/(const float other)
{
	return Vector2( X/other, Y/other);
}

void Vector2::Add(Vector2* v)
{
	X += v->X;
	Y += v->Y;
}

void Vector2::operator+=(const Vector2&  other)
{
	X+=other.X;
	Y+=other.Y;
}

void Vector2::operator-=(const Vector2&  other)
{
	X-=other.X;
	Y-=other.Y;
}

void Vector2::operator*=(const float other)
{
	X*=other;
	Y*=other;
}

void Vector2::operator/=(const float other)
{
	X/=other;
	Y/=other;
}
