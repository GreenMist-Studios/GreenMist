#ifndef WORLD_H
#define WORLD_H

#include <map>
#include <vector>
#include <typeinfo>
#include <algorithm>
#include "Manager.h"
#include "ComponentManager.h"
//#include "ComponentMapper.h"
//#include "EntityManager.h"
#include "Entity.h"
#include "EntityObserver.h"
#include "ImmutableBag.h"
#include "EntitySystem.h"

//class Manager;
class ComponentManager;
class EntityManager;
class EntitySystem;

template<class T>
class ComponentMapper;

struct comp {
    bool operator ()(const std::type_info* a, const std::type_info* b) const {
        return a->before(*b);
    }
};

class Performer
{
public:
    virtual void perform(EntityObserver* observer, Entity* e){}
};

class AddedPerformer : public Performer
{
 void perform(EntityObserver* observer, Entity* e)
    {
        observer->Added(e);
    }
};

class ChangedPerformer : public Performer
{
void perform(EntityObserver* observer, Entity* e)
    {
        observer->Changed(e);
    }
};

class DeletedPerformer : public Performer
{
void perform(EntityObserver* observer, Entity* e)
    {
        observer->Deleted(e);
    }
};


class EnabledPerformer : public Performer
{
void perform(EntityObserver* observer, Entity* e)
    {
        observer->Enabled(e);
    }
};

class DisabledPerformer : public Performer
{
void perform(EntityObserver* observer, Entity* e)
    {
        observer->Disabled(e);
    }
};

class World
{
    public:
        World();
        virtual ~World();

        void Initialize();
        EntityManager* GetEntityManager();
        ComponentManager* GetComponentManager();

        template<class T>
        T* SetManager(T* manager);
        template<class T>
        T* GetManager();
        void DeleteManager(Manager* manager);

        float GetDelta();
        void SetDelta(float f);

        void AddEntity(Entity* e);
        void ChangedEntity(Entity* e);
        void DeleteEntity(Entity* e);
        void Enable(Entity* e);
        void Disable(Entity* e);

        Entity* CreateEntity();
        Entity* GetEntity(int entityId);

        void Process();

        Bag<EntitySystem*>* GetSystems();

        template<typename T>
        T* SetSystem(T* system)
        {
            return SetSystem(system, false);
        }
        template<typename T>
        T* SetSystem(T* system, bool passive)
        {
            system->SetWorld(this);
            system->SetPassive(passive);

            systems[&typeid(T)] = system;
            systemsArray->add(system);

            return (T*) system;
        }

        void DeleteSystem(EntitySystem* system);
        template<class T>
        T GetSystem();

        template<class T>
        ComponentMapper<T> getMapper();

    protected:
    private:
        void Check(Bag<Entity*>* entities, Performer* performer);
        void NotifySystems(Performer* performer, Entity* e);
        void NotifyManagers(Performer* performer, Entity* e);

        float delta;

        ComponentManager* componentManager;
        EntityManager* entityManager;

        Bag<Entity*>* added;
        Bag<Entity*>* changed;
        Bag<Entity*>* deleted;
        Bag<Entity*>* enable;
        Bag<Entity*>* disable;

        std::map<const std::type_info*, Manager*, comp> managers;
        Bag<Manager*>* managersArray;
        std::map<const std::type_info*, EntitySystem*, comp> systems;
        Bag<EntitySystem*>* systemsArray;
};

#endif
