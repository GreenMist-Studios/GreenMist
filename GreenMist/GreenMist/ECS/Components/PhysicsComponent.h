#pragma once
#include <Box2D/Box2D.h>
#include <vector>

class PhysicsComponent : public Component
{
public:
	PhysicsComponent(b2BodyDef* bd, bool ControlComponents, b2FixtureDef* fixdef, ...)
	{
        va_list args;
		BodyDef = bd;
		Fixtures = std::vector<b2FixtureDef*>();
		
		for (va_start(args, fixdef); fixdef != NULL; fixdef = va_arg(args, b2FixtureDef*))
		{
			Fixtures.push_back(fixdef);
        }
        va_end(args);

		ControlOtherComponents = ControlComponents;
		World = NULL;
		Body = NULL;
	}

	PhysicsComponent(b2BodyDef* bd, b2FixtureDef* fixdef, ...)
	{
        va_list args;
		BodyDef = bd;
		Fixtures = std::vector<b2FixtureDef*>();
		
		for (va_start(args, fixdef); fixdef != NULL; fixdef = va_arg(args, b2FixtureDef*))
		{
			Fixtures.push_back(fixdef);
        }
        va_end(args);

		ControlOtherComponents = false;
		World = NULL;
		Body = NULL;
	}

	b2BodyDef* BodyDef;
	std::vector<b2FixtureDef*> Fixtures;

	b2Body* Body;
	b2World* World;

	bool ControlOtherComponents;
};

