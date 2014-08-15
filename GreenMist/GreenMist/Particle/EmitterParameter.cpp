#include "EmitterParameter.h"

EmitterParameter::EmitterParameter(void)
{
    Quantity = Range(1);
    Speed = RangeF(-1.0f,1.0f);
    SDL_Color c = { 0,255,0 };
    SDL_Color c2 = { 255,0,255 };
    Color = RangeColor(c,c2);
    Opacity = RangeF(1.0f,1.0f);
    Scale = RangeF(1.0f, 10.0f);
    Rotation = RangeF(-(float)M_PI, (float)M_PI);
	AngularVelocity = RangeF(-1.0f, 1.0f);
    Mass = RangeF(1.0f);
}

EmitterParameter::~EmitterParameter()
{

}

EmitterParameter::EmitterParameter(Range q, RangeF spd, SDL_Color col1, SDL_Color col2, RangeF o, RangeF scl, RangeF rot,  RangeF ang,RangeF m)
{
    Quantity = q;
    Speed = spd;
    Color = RangeColor(col1,col2);
    Opacity = o;
    Scale = scl;
    Rotation = rot;
	AngularVelocity = ang;
    Mass = m;
}
