#ifndef COMPONENTMAPPER_H
#define COMPONENTMAPPER_H

//#include "ECS/ComponentManager.h"
#include <vector>
#include "ComponentType.h"
#include "Component.h"
#include "ComponentManager.h"
#include "World.h"
//class World;
class Entity;

template <class T>
class ComponentMapper
{
    public:
        ComponentMapper(World* w)
        {
            type = ComponentType::GetTypeFor(&typeid(T));
            classType = &typeid(T);
            components = w->GetComponentManager()->GetComponentsByType(type);
        }


        T Get(Entity* e)
        {
            return (T) components->get(e->GetId());
        }

        T GetSafe(Entity* e)
        {
            if (e->GetId() < components->getCount())
            {
                return (T) components->get(e->GetId());
            }
            return NULL;
        }


        bool Has(Entity* e)
		{
			 return GetSafe(e) != NULL;
		}

        template <class C>
        static ComponentMapper<C> GetFor(World* w)
        {
            return new ComponentMapper<C>(w);
        }

    protected:
    private:
        ComponentType* type;
        const std::type_info* classType;
        Bag<Component*>* components;
};

#endif // COMPONENTMAPPER_H
