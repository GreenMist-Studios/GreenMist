#pragma once
#include <math.h>
#include <algorithm>

class Range
{
public:
	Range(void);
	Range(int value);
	Range(int x, int y);
	~Range(void);

	int X;
	int Y;
	int Diameter;
	int Radius;
	int Center;


};

