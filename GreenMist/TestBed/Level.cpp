#include "Level.h"

Level::Level()
{
	//ctor
	b2Vec2 gravity(0.0f, 10.0f);

	world = new b2World(gravity);
}

Level::~Level()
{
	//dtor
}

void Level::AddModule(Module* module)
{
	for (std::vector<TMXObjectGroupLayer*>::iterator it = module->tmxMap->ObjectGroupLayers.begin(); it != module->tmxMap->ObjectGroupLayers.end(); ++it)
	{
		TMXObjectGroupLayer* ogl = (*it);
		for (std::vector<Object*>::iterator iit = ogl->Objects.begin(); iit != ogl->Objects.end(); ++iit)
		{
			Object* obj = (*iit);

			if (obj->Type == "Collision" && obj->ObjectType == PolyLine)
			{
				b2BodyDef bd;

				bd.type = b2_staticBody;
				bd.position = RealToSimConvert(obj->GetPosition()/100);
				bd.userData = this;

				module->collisionBody = world->CreateBody(&bd);

				b2Vec2* verts =  (b2Vec2*)malloc(obj->Points.size()-1 * sizeof(b2Vec2));
				for (int j = 0; j < obj->Points.size()-1; j ++)
				{
					verts[j] = RealToSimConvert(obj->Points[j]);
				}

				b2ChainShape shape;
				shape.CreateChain(verts, obj->Points.size()-1);

				module->collisionBody->CreateFixture(&shape,1);
			}
		}
	}

	Modules.push_back(module);
}

void Level::Draw()
{
	for (std::vector<Module*>::iterator it = Modules.begin(); it != Modules.end(); ++it)
	{
		(*it)->Draw();
	}
}

void Level::DebugDraw()
{
	if (Settings::Debug)
		world->DrawDebugData();
}
