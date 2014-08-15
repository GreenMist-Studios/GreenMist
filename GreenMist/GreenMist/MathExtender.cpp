#include "MathExtender.h"

MathExtender::MathExtender()
{
	srand((int)time(NULL));
}

int MathExtender::Random(Range r)
{
	return Random(r.X, r.Y);
}

float MathExtender::Random(RangeF r)
{
	return Random(r.X, r.Y);
}

SDL_Color MathExtender::Random(RangeColor r)
{
	float progress = RandomFloat();
    float q = 1 - progress;

    SDL_Color color = SDL_Color();
    color.r = (Uint8)(r.Min.r * q) + (Uint8)(r.Max.r * progress);
    color.g = (Uint8)(r.Min.g * q) + (Uint8)(r.Max.g * progress);
    color.b = (Uint8)(r.Min.b * q) + (Uint8)(r.Max.b * progress);
    color.a = 255;
    return color;
}

SDL_Color* MathExtender::RandomColor(RangeColor r)
{
	float progress = RandomFloat();
    float q = 1 - progress;

    SDL_Color* color = new SDL_Color();
    color->r = (Uint8)(r.Min.r * q) + (Uint8)(r.Max.r * progress);
    color->g = (Uint8)(r.Min.g * q) + (Uint8)(r.Max.g * progress);
    color->b = (Uint8)(r.Min.b * q) + (Uint8)(r.Max.b * progress);
    color->a = 255;
    return color;
}

int MathExtender::Random(int hi, int low)
{
	if (hi == low)
		return hi;

	int l = std::min(low, hi);
	int h = std::max(low, hi);
	return l + static_cast <int> (rand()) /( static_cast <int> (RAND_MAX/(h-l)));
}

float MathExtender::Random(float hi, float low)
{
	if (hi == low)
		return hi;

	float l = std::min(low, hi);
	float h = std::max(low, hi);
	return l + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(h-l)));
}

float MathExtender::RandomFloat()
{
	return (float)(rand()) / (float)(RAND_MAX);
}

Vector2 MathExtender::RandomUnitVector()
{
	float r = (float)(rand()) / (float)(RAND_MAX);
	float r2 = (float)(rand()) / (float)(RAND_MAX);

	return Vector2(r,r2);
}

Vector2* MathExtender::RandomUnitVectorP()
{
	float r = (float)(rand()) / (float)(RAND_MAX);
	float r2 = (float)(rand()) / (float)(RAND_MAX);

	return new Vector2(r,r2);
}

float MathExtender::RandomAngle()
{
	int rand = Random(0,360);
	return rand * M_PI / 180;
}

Vector2 MathExtender::RandomVectorFromAngle()
{
	float angle = RandomAngle();
	return Vector2(cosf(angle),sinf(angle));
}

Vector2* MathExtender::RandomVectorFromAngleP()
{
	float angle = RandomAngle();
	return new Vector2(cosf(angle),sinf(angle));
}



float MathExtender::Clamp(float num, float hi, float low)
{
	int l = std::min(low, hi);
	int h = std::max(low, hi);
	if (num < l)
        return l;
    else if (num > h)
        return h;
    else
        return num;
}
