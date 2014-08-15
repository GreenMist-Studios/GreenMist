#pragma once

#include <Box2D/Box2D.h>
#include "../EntitySystem.h"
#include "../ComponentMapper.h"
#include "../Components/PhysicsComponent.h"
#include "../Components/PositionComponent.h"
#include "../Components/RotationComponent.h"
#include "../../Vector2.h"
#include "../../MathExtender.h"
#include "../../B2DDebugDraw.h"
#include "../../TextureManager.h"


class PhysicsEntitySystem : public EntitySystem
{
	public:
		PhysicsEntitySystem(float step, Vector2 gravity, int velIter, int posIter): EntitySystem(&typeid(this), Aspect::GetAspectForAll(&typeid(PhysicsComponent*),&typeid(PositionComponent*), NULL))
		{
			World = new b2World(Convert(gravity));
			Step = step;
			VelocityIterations = velIter;
			PositionIterations = posIter;

			counter = 0;

			b2Draw* DebugDraw = new B2DDebugDraw(TextureManager::GetRenderer());
			DebugDraw->SetFlags(DebugDraw->e_shapeBit);
			World->SetDebugDraw(DebugDraw);
		}
		
		void Initialize()
		{
             pcm = new ComponentMapper<PhysicsComponent*>(world);
             poscm = new ComponentMapper<PositionComponent*>(world);
             rcm = new ComponentMapper<RotationComponent*>(world);
		}
		
        bool CheckProcessing()
		{ 
			return true;
		}

		void ProcessEntities(std::vector<Entity*>* entities) 
		{
			counter += world->GetDelta();
			if (counter >= Step)
			{
				counter -= Step;
				World->Step(Step, VelocityIterations, PositionIterations);
			}

			for (int i = 0, s = entities->size(); s > i; i++)
            {
                if (entities->at(i) != NULL)
                {
                    ProcessEntity(entities->at(i));
                }
            }
        }
		
        void ProcessEntity(Entity* e)
		{
			PhysicsComponent* pc = pcm->GetSafe(e);

			if (pc->ControlOtherComponents)
			{
				PositionComponent* posc = poscm->GetSafe(e);

				posc->x = SimToRealConvert(pc->Body->GetPosition()).X;
				posc->y = SimToRealConvert(pc->Body->GetPosition()).Y;

				RotationComponent* rc = rcm->GetSafe(e);
				if (rc != NULL)
					rc->angle = pc->Body->GetAngle(); 
			}
		}

		void Inserted(Entity* e) 
		{
			PhysicsComponent* pc = pcm->GetSafe(e);
			if (pc == NULL)
				return;

			if (pc->World == NULL)
			{
				pc->World = World;
				pc->Body = World->CreateBody(pc->BodyDef);
				
				for ( int i = 0; i < pc->Fixtures.size(); i++)
				{
					pc->Body->CreateFixture(pc->Fixtures[i]);
				}
			}
		}

		int VelocityIterations;
		int PositionIterations;
		float Step;

		ComponentMapper<PhysicsComponent*>* pcm;
		ComponentMapper<PositionComponent*>* poscm;
		ComponentMapper<RotationComponent*>* rcm;

		b2World* World;

private:
		float counter;
};