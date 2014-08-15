#ifndef MANAGER_H
#define MANAGER_H

#include <typeinfo>
#include "EntityObserver.h"

class World;

class Manager : public EntityObserver
{
public:
    Manager()
	{
		world = NULL;
	}

    virtual void Initialize(){};

    const std::type_info* id;

    void SetWorld(World* w)
    {
        world = w;
    }

    World* GetWorld()
    {
        return world;
    }

protected:
    World* world;
};

#endif
