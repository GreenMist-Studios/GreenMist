#pragma once

#include "IntervalEntityProcessingSystem.h"
#include "../ComponentMapper.h"
#include "../Components/PositionComponent.h"
#include "../Components/TextureComponent.h"
#include "../Components/VelocityComponent.h"
#include "../Components/EmitterComponent.h"


class ParticleEntitySystem : public IntervalEntityProcessingSystem
{
    public:
		
		ParticleEntitySystem(float interval) : IntervalEntityProcessingSystem(&typeid(this), Aspect::GetAspectForAll(&typeid(EmitterComponent*), NULL), interval) 
		{
		}

        void Initialize()
		{
            ecm = new ComponentMapper<EmitterComponent*>(world);
		}

        void ProcessEntity(Entity* e)
		{
			EmitterComponent* ec = ecm->GetSafe(e);
			
            if (ec->Collection->Count() == 0)
                return;

			ec->totalSeconds += world->GetDelta();
			ec->secondsSinceLastReclaim +=  world->GetDelta();

            if (ec->secondsSinceLastReclaim > ec->ReclaimInterval)
            {
                ec->ReclaimParticles();
                ec->secondsSinceLastReclaim = 0;
            }

			for (int i = 0; i < (int)ec->Modifiers->Slots.size(); i++)
            {
                 ec->Modifiers->Slots[i].Update(ec->Collection, world->GetDelta());
            }
		}

    private:
        ComponentMapper<EmitterComponent*>* ecm;
};

