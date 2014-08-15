#include "RangeColor.h"


RangeColor::RangeColor(void)
{
	Min = SDL_Color();
	Max = SDL_Color();
}

RangeColor::RangeColor(SDL_Color color)
{
	Min = color;
	Max = color;
}

RangeColor::RangeColor(SDL_Color min, SDL_Color max)
{
	Min = min;
	Max = max;
}

RangeColor::~RangeColor(void)
{
}
