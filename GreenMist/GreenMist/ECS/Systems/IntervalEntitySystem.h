#ifndef INTERVALENTITYSYSTEM_H
#define INTERVALENTITYSYSTEM_H

#include "../EntitySystem.h"

class IntervalEntitySystem : public EntitySystem
{
    public:
        IntervalEntitySystem(const type_info* type, Aspect* aspect, float ival) : EntitySystem(type, aspect)
        {
            interval = ival;
			acc = 0.0f;
        }

        bool CheckProcessing();
    private:
        float acc;
        float interval;
};

#endif // INTERVALENTITYSYSTEM_H
