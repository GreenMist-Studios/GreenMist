#pragma once

#include "../Component.h"

class RotationComponent :
	public Component
{
public:
	RotationComponent()
	{
		angle = 0.0f;
	}

	RotationComponent(float ang)
	{
		angle = ang;
	}

float angle;
};