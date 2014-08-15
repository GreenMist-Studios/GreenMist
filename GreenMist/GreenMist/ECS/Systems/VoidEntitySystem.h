#ifndef VOIDENTITYSYSTEM_H
#define VOIDENTITYSYSTEM_H

#include "../EntitySystem.h"

class VoidEntitySystem : public EntitySystem
{
    public:
        VoidEntitySystem() : EntitySystem(Aspect::GetEmpty()){}

        void ProcessEntities(std::vector<Entity*>* entities) {
            ProcessSystem();
        }
        virtual void ProcessSystem();
        bool CheckProcessing()
        {
            return true;
        }
};

#endif // VOIDENTITYSYSTEM_H
