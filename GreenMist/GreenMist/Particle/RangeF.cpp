#include "RangeF.h"


RangeF::RangeF(void)
{
	X = 0;
	Y = 0;
}

RangeF::RangeF(float x, float y)
        {
            X = std::min(x,y);
            Y = std::max(x, y);

            Diameter = fabs(X - Y);
            Radius = Diameter / 2;
            Center = X + Radius;
        }

RangeF::RangeF(float value)
{
	X = value;
	Y = value;

    Diameter = fabs(X - Y);
    Radius = Diameter / 2;
    Center = X + Radius;
}

RangeF::~RangeF(void)
{
}

