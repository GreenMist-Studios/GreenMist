#ifndef RENDERORDERSYSTEM_H
#define RENDERORDERSYSTEM_H

#include <SDL2/SDL.h>
#include <algorithm>
#include <ECS/ComponentMapper.h>
#include <ECS/Systems/EntityProcessingSystem.h>
#include <ECS/Components/PositionComponent.h>
#include <ECS/Components/RenderOrderComponent.h>
#include <ECS/Components/EmitterComponent.h>
#include <ECS/Components/RotationComponent.h>
#include <ECS/Systems/PhysicsEntitySystem.h>
#include <Particle/Particle.h>
#include <MathExtender.h>


class RenderOrderSystem : public EntityProcessingSystem
{
    public:
        RenderOrderSystem() : EntityProcessingSystem(&typeid(this), Aspect::GetAspectForAll(&typeid(PositionComponent*), &typeid(RenderOrderComponent*),NULL))
		{
		}

        void Initialize()
        {
            rocm = new ComponentMapper<RenderOrderComponent*>(world);
            pcm = new ComponentMapper<PositionComponent*>(world);
            rcm = new ComponentMapper<RotationComponent*>(world);
        }

        void ProcessEntity(Entity* e)
        {
            PositionComponent* pc = pcm->GetSafe(e);
            RenderOrderComponent* roc = rocm->GetSafe(e);
			RotationComponent* rc = rcm->GetSafe(e);

			if ( roc->CheckRenderOrderChanged())
				Sort();
			
			if (roc->texture != NULL)
			{
				double angle = 0.0;

				if (rc != NULL)
					angle = rc->angle;

				roc->texture->setAlpha(255 * roc->Opacity);
				SDL_Point center;
				center.x = roc->texture->getWidth()/2;
				center.y = roc->texture->getHeight()/2;

				roc->texture->render(pc->x - center.x, pc->y - center.y, NULL, RadianToDegree(angle), &center);
			}

			//Render Particle System
			EmitterComponent* ec = (EmitterComponent*) e->GetComponent(&typeid(EmitterComponent*));
			if (ec != NULL)
			{
				std::vector<Particle*> collection = ec->Collection->Particles;
				for (int i = 0; i <collection.size(); i++)
				{
					Particle* p = collection[i];

					Texture* texture = TextureManager::Get(p->Texture);
					texture->setAlpha((Uint8)(p->Opacity * 255));
					texture->setColor(p->Color.r, p->Color.g, p->Color.b); 
					texture->setBlendMode(ec->BlendMode);
					texture->render(p->Position.X, p->Position.Y, NULL, p->Rotation, NULL);
					texture->setAlpha(255);
				}
			}
        }

		void Inserted(Entity* e)
		{
			Sort();
		}

		void Sort();

    private:
        ComponentMapper<PositionComponent*>* pcm;
        ComponentMapper<RenderOrderComponent*>* rocm;
		ComponentMapper<RotationComponent*>* rcm;
};

#endif // RENDERORDERSYSTEM_H
