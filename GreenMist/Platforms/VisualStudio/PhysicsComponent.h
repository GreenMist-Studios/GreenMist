#pragma once
#include <Box2D\Box2D.h>
#include <vector>

class PhysicsComponent
{
public:
	PhysicsComponent(b2BodyDef* bd)
	{
		BodyDef = bd;
	}

	b2BodyDef* BodyDef;

	b2Body* Body;
	b2World* World;
};

