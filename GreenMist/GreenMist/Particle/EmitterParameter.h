#pragma once
#include "Range.h"
#include "RangeF.h"
#include "RangeColor.h"
#include "../GMApplication.h"
#include <SDL2/SDL.h>
#include <math.h>

class EmitterParameter
{
public:
	EmitterParameter();
	EmitterParameter(Range q, RangeF spd, SDL_Color col1, SDL_Color col2, RangeF o, RangeF scl, RangeF rot, RangeF ang, RangeF m);
	~EmitterParameter(void);

	Range Quantity;
    RangeF Speed;
    RangeColor Color;
    RangeF Opacity;
    RangeF Scale;
    RangeF Rotation;
	RangeF AngularVelocity;
    RangeF Mass;
};

