#pragma once

#include <Box2D/Box2D.h>
#include "../MathExtender.h"

class PhysicsFactory
{
public:
	static b2BodyDef* CreateBasicBodyDef(float x, float y, float angle, b2BodyType type, void* userdata)
	{
		b2BodyDef* bd = new b2BodyDef();
		bd->active = true;
		bd->angle = angle;
		bd->position.Set(RealToSim(x),RealToSim(y));
		bd->type = type;
		bd->userData = userdata;
		return bd;
	}

	static b2FixtureDef* CreateRectangleFixture(int w, int h, float density)
	{
		b2PolygonShape* boxShape = new b2PolygonShape();
		boxShape->SetAsBox(RealToSim(w)/2.0f,RealToSim(h)/2.0f);

		b2FixtureDef* boxFixtureDef = new b2FixtureDef();
		boxFixtureDef->shape = boxShape;
		boxFixtureDef->density = 1;

		return boxFixtureDef;
	}

	static b2FixtureDef* CreateCircleFixture(int r, float density)
	{
		b2CircleShape* shape = new b2CircleShape();
		shape->m_radius = r;
		
		b2FixtureDef* boxFixtureDef = new b2FixtureDef();
		boxFixtureDef->shape = shape;
		boxFixtureDef->density = 1;
		
		return boxFixtureDef;
	}

	static b2FixtureDef* CreatePolyLine(const b2Vec2* verts, int count)
	{
		b2ChainShape shape;
		shape.CreateChain(verts, count);
		
		b2FixtureDef boxFixtureDef;
		boxFixtureDef.shape = &shape;
		boxFixtureDef.density = 1;
		
		return &boxFixtureDef;
	}
};