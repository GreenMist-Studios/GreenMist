#pragma once
#include <math.h>
#include <algorithm>

class RangeF
{
public:
	RangeF(void);
	RangeF(float value);
	RangeF(float x, float y);
	~RangeF(void);

	float X;
	float Y;
	float Diameter;
	float Radius;
	float Center;
};

