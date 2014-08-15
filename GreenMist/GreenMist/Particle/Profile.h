#pragma once
#include "../Vector2.h"
#include "../MathExtender.h"


class Profile
{
public:
	Profile();
	virtual void GetOffsetAndHeading(Vector2& offset, Vector2& heading);
};

class PointProfile : public Profile
{
public:
	PointProfile();
		void GetOffsetAndHeading(Vector2& offset, Vector2& heading);
};

class CircleProfile : public Profile
{
public:
		CircleProfile(float radius, bool radiate);
        float Radius;
        bool Radiate;
		void GetOffsetAndHeading(Vector2& offset, Vector2& heading);
};

class BoxProfile : public Profile
{
public:
	BoxProfile(float width, float height);
	float Width;
    float Height;
		void GetOffsetAndHeading(Vector2& offset, Vector2& heading);
};

class RingProfile : public Profile
{
public:
		RingProfile(float radius, bool radiate);
        float Radius;
        bool Radiate;
		void GetOffsetAndHeading(Vector2& offset, Vector2& heading);
};

class BoxFillProfile : public Profile
{
public:
		BoxFillProfile(float width, float height);
		float Width;
		float Height;
		void GetOffsetAndHeading(Vector2& offset, Vector2& heading);
};