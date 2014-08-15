#ifndef MATHEXTENDER_
#define MATHEXTENDER_

#include <string>
#include <functional>
#include <cctype>
#include <locale>
#include <algorithm>
#include <cstdlib>
#include <stdio.h>
#include <math.h>
#include <ctime>
#include <Box2D/Box2D.h>
#include "Vector2.h"
#include "Particle/Range.h"
#include "Particle/RangeF.h"
#include "Particle/RangeColor.h"

class MathExtender
{
public:
	MathExtender();

	static float Random(RangeF r);
	static int Random(Range r);
	static SDL_Color Random(RangeColor r);
	static SDL_Color* RandomColor(RangeColor r);
	static int Random(int hi, int lo);
	static float Random(float hi, float low);
	static float RandomFloat();
	static Vector2 RandomUnitVector();
	static Vector2* RandomUnitVectorP();
	static float RandomAngle();
	static Vector2 RandomVectorFromAngle();
	static Vector2* RandomVectorFromAngleP();

	static float Clamp(float num, float hi, float low);
};

inline b2Vec2 Convert(Vector2 v)
{
    b2Vec2 vv;
    vv.Set(v.X,v.Y);
    return vv;
}

inline Vector2 Convert(b2Vec2 v)
{
    Vector2 vv = Vector2(v.x,v.y);
    return vv;
}

inline float SimToReal(float val)
{
    return val * 100.0f;
}
inline float RealToSim(float val)
{
    return val / 100.0f;
}

inline Vector2 SimToRealConvert(b2Vec2 val)
{
    Vector2 v = Convert(val);
    v *= 100;
    return v;
}

inline b2Vec2 RealToSimConvert(Vector2 val)
{
    b2Vec2 ven = Convert(val);
    ven.x /= 100;
    ven.y /= 100;
    return ven;
}

inline float RadianToDegree(float ang)
{
	return ang * 180 / M_PI;
}
#endif
