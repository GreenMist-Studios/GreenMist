#include "Range.h"


Range::Range(void)
{
	X = 0;
	Y = 0;
}

Range::Range(int x, int y)
        {
            X = std::min(x,y);
            Y = std::max(x, y);

            Diameter = fabs((float)(X - Y));
            Radius = Diameter / 2;
            Center = X + Radius;
        }

Range::Range(int value)
{
	X = value;
	Y = value;

    Diameter = fabs((float)(X - Y));
    Radius = Diameter / 2;
    Center = X + Radius;
}

Range::~Range(void)
{
}

