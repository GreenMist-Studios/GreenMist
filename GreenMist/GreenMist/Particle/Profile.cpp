#include "Profile.h"

Profile::Profile()
{
}

void Profile::GetOffsetAndHeading(Vector2& offset, Vector2& heading)
{
}

RingProfile::RingProfile(float radius, bool radiate)
{
	Radius = radius;
	Radiate = radiate;
}

BoxProfile::BoxProfile(float width, float height)
{
	Width = width;
	Height = height;
}

BoxFillProfile::BoxFillProfile(float width, float height)
{
	Width = width;
	Height = height;
}

CircleProfile::CircleProfile(float radius, bool radiate)
{
	Radius = radius;
	Radiate = radiate;
}

void PointProfile::GetOffsetAndHeading(Vector2& offset, Vector2& heading)
{
	offset = Vector2();
	heading = MathExtender::RandomVectorFromAngle();
}

void CircleProfile::GetOffsetAndHeading(Vector2& offset, Vector2& heading)
{
    float dist = MathExtender::Random((float)0, Radius);

    heading = MathExtender::RandomUnitVector();

	offset = Vector2(heading.X * dist, heading.Y * dist);

    if (!Radiate)
		heading = MathExtender::RandomVectorFromAngle();
}

void RingProfile::GetOffsetAndHeading(Vector2& offset, Vector2& heading)
{

    heading = MathExtender::RandomVectorFromAngle();

	offset = Vector2(heading.X * Radius, heading.Y * Radius);

    if (!Radiate)
		heading = MathExtender::RandomVectorFromAngle();
}

void BoxProfile::GetOffsetAndHeading(Vector2& offset, Vector2& heading)
{
	switch (MathExtender::Random(0,4))
            {
                case 0: // Left
                        offset = Vector2(Width * -0.5f, MathExtender::Random(Height * -0.5f, Height * 0.5f));
                        break;
                case 1: // Top
                        offset = Vector2(MathExtender::Random(Width * -0.5f, Width * 0.5f), Height * -0.5f);
                        break;
                case 2: // Right
                        offset = Vector2(Width * 0.5f, MathExtender::Random(Height * -0.5f, Height * 0.5f));
                        break;
                case 3: // Bottom
                        offset = Vector2(MathExtender::Random(Width * -0.5f, Width * 0.5f), Height * 0.5f);
                        break;
            }

            heading = MathExtender::RandomUnitVector();
}


void BoxFillProfile::GetOffsetAndHeading(Vector2& offset, Vector2& heading)
{
	 offset = Vector2(MathExtender::Random(Width * -0.5f, Width * 0.5f),
                                     MathExtender::Random(Height * -0.5f, Height * 0.5f));
	 
     heading = MathExtender::RandomUnitVector();
}