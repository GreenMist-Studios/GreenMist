#ifndef COMPONENTMANAGER_H
#define COMPONENTMANAGER_H

#include <vector>
#include <bitset>
//#include "Entity.h"
#include "Component.h"
#include "ComponentType.h"
#include "ImmutableBag.h"
#include "Manager.h"
#include "World.h"

class Entity;

class ComponentManager : public Manager
{
    public:

        ComponentManager()
        {
            deleted = Bag<Entity*>(0);
            componentsByType = new Bag<Bag<Component*>*>();
        };

        void Initialize(){};

        void AddComponent(Entity* e, ComponentType* type, Component* component);

        void RemoveComponent(Entity* e, ComponentType* type);


        Bag<Component*>* GetComponentsByType(ComponentType* type);

        Component* GetComponent(Entity* e, ComponentType* type);

        Bag<Component*> GetComponentsFor(Entity* e, Bag<Component*> fillVector);


        void Deleted(Entity* e);


        void Clean();

private:
        void RemoveComponentsOfEntity(Entity* e);


        Bag<Bag<Component*>* >* componentsByType;
        Bag<Entity*> deleted;
};

#endif // COMPONENTMANAGER_H
