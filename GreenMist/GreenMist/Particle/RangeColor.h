#pragma once
#include <SDL2/SDL.h>

class RangeColor
{
public:
	RangeColor(void);
	RangeColor(SDL_Color color);
	RangeColor(SDL_Color min, SDL_Color max);
	~RangeColor(void);

	SDL_Color Min;
	SDL_Color Max;
};

