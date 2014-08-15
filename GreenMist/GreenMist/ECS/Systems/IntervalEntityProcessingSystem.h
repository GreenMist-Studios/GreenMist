#ifndef INTERVALENTITYPROCESSINGSYSTEM_H
#define INTERVALENTITYPROCESSINGSYSTEM_H

#include "IntervalEntitySystem.h"

class IntervalEntityProcessingSystem : public IntervalEntitySystem
{
    public:
        IntervalEntityProcessingSystem(const type_info* type, Aspect* a, float ival) : IntervalEntitySystem(type, a,ival)
        {

        }

		virtual void ProcessEntity(Entity* e)
		{
		}

		void ProcessEntities(std::vector<Entity*>* entities)
        {
            for (int i = 0, s = entities->size(); s > i; i++) {
                ProcessEntity(entities->at(i));
            }
        }

    protected:
    private:
};

#endif // INTERVALENTITYPROCESSINGSYSTEM_H
