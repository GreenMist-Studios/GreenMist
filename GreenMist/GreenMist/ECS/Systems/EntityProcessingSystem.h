#ifndef ENTITYPROCESSINGSYSTEM_H
#define ENTITYPROCESSINGSYSTEM_H

#include "../EntitySystem.h"

class EntityProcessingSystem : public EntitySystem
{
    public:
		EntityProcessingSystem(const std::type_info* type, Aspect* aspect) : EntitySystem(type, aspect){}

        virtual void ProcessEntity(Entity* e){}

		void ProcessEntities(std::vector<Entity*>* entities)
        {
            for (int i = 0, s = entities->size(); s > i; i++)
            {
                if (entities->at(i) != NULL)
                {
                    ProcessEntity(entities->at(i));
                }
            }
        }
		bool CheckProcessing()
        {
            return true;
        }
};

#endif // ENTITYPROCESSINGSYSTEM_H
