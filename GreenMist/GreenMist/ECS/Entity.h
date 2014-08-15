#ifndef ENTITY_H
#define ENTITY_H

#include <iostream>
#include <bitset>
#include <string>
#include <sstream>
#include "Bitsize.h"
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include "ComponentManager.h"
#include "World.h"
#include "Component.h"
#include "ComponentType.h"
#include "EntityManager.h"

class ComponentManager;

using namespace boost::uuids;

class Entity
{
    public:
        Entity(World* world, int id);

        int GetId() { return id; };

        std::bitset<BITSIZE>* GetComponentBits()
        {
            return componentBits;
        }

        std::bitset<BITSIZE>* GetSystemBits()
        {
            return systemBits;
        }

        void Reset()
        {
            systemBits->reset();
            componentBits->reset();
            UUID = random_generator()();
        }

        const char* ToString()
        {
            std::stringstream s;
            s << "Entity[" << id << "]";
            return s.str().c_str();
		}

        template<class T>
        Entity* AddComponent(T* component)
        {
            return Work(component, ComponentType::GetTypeFor(&typeid(component)));
        }

        Entity* AddComponent(Component* component, ComponentType* type);

        Entity* RemoveComponent(Component* component);
        Entity* RemoveComponent(ComponentType* type);
        Entity* RemoveComponent(const std::type_info* type);

        bool IsActive();
        bool IsEnabled();

        Component* GetComponent(ComponentType* type);
        Component* GetComponent(const std::type_info* type);

        template<class T>
        T GetComponent(T null);

        Bag<Component*> GetComponents(Bag<Component*> fillBag);

        void AddToWorld();
        void ChangedInWorld();
        void DeleteFromWorld();
        void Enable();
        void Disable();

        uuid GetUuid()
        {
            return UUID;
        }
        World* GetWorld()
        {
            return world;
        }

protected:
private:
        Entity* Work(Component* component, ComponentType* type);

        uuid UUID;
        long id;
        std::bitset<BITSIZE>* componentBits;
        std::bitset<BITSIZE>* systemBits;

        World* world;
        EntityManager* entityManager;
        ComponentManager* componentManager;
};

#endif // ENTITY_H
