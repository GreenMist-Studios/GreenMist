#include "World.h"

World::World()
{
    //ctor
    componentManager = new ComponentManager();
    entityManager = new EntityManager();

    managersArray = new Bag<Manager*>(0);
    systemsArray = new Bag<EntitySystem*>(0);

	managers = std::map<const std::type_info*, Manager*, comp>();
	systems = std::map<const std::type_info*, EntitySystem*, comp>();

    SetManager<ComponentManager>(componentManager);
    SetManager<EntityManager>(entityManager);

	delta = 0;

    added = new Bag<Entity*>(0);
    changed = new Bag<Entity*>(0);
    disable = new Bag<Entity*>(0);
    enable = new Bag<Entity*>(0);
    deleted = new Bag<Entity*>(0);
}

World::~World()
{
    //dtor
}

void World::Initialize()
{
    for (int i = 0; i < managersArray->getCount(); i++)
    {
        managersArray->get(i)->Initialize();
    }

	for (int i = 0; i < systemsArray->getCount(); i++)
    {
        systemsArray->get(i)->Initialize();
    }
}

EntityManager* World::GetEntityManager()
{
    return entityManager;
}

ComponentManager* World::GetComponentManager()
{
    return componentManager;
}

template<class T>
T* World::SetManager(T* manager)
{
    manager->id = &typeid(T);
    manager->SetWorld(this);
    managers[&typeid(T)] = manager;
    managersArray->add(manager);
    return (T*)manager;
}

template<class T>
T* World::GetManager()
{
    return (T*) managers[&typeid(T)];
}

void World::DeleteManager(Manager* manager)
{
    managers.erase(manager->id);
    managersArray->remove(manager);
}

float World::GetDelta()
{
    return delta;
}

void World::SetDelta(float d)
{
    delta = d;
}

void World::AddEntity(Entity* e)
{
    added->add(e);
}

void World::ChangedEntity(Entity* e)
{
    changed->add(e);
}

void World::DeleteEntity(Entity* e)
{
    if(!deleted->contains(e))
    {
        deleted->add(e);
    }
}

void World::Enable(Entity* e)
{
    enable->add(e);
}

void World::Disable(Entity* e)
{
    disable->add(e);
}

Entity* World::CreateEntity()
{
    return entityManager->CreateEntityInstance();
}

Entity* World::GetEntity(int entityId)
{
    return entityManager->GetEntity(entityId);
}

Bag<EntitySystem*>* World::GetSystems()
{
    return systemsArray;
}

template<class T>
T World::GetSystem()
{
    return systems[&typeid(T)];
}

void World::NotifySystems(Performer* performer, Entity* e)
{
    for(int a = 0; systemsArray->getCount() > a; a++) {
        performer->perform(systemsArray->get(a), e);
    }
}

void World::NotifyManagers(Performer* performer, Entity* e)
{
    for(int a = 0; managersArray->getCount() > a; a++) {
        performer->perform(managersArray->get(a), e);
    }
}

void World::Check(Bag<Entity*>* entities, Performer* performer)
{
    if (!entities->isEmpty())
    {
        for (int i = 0; i < entities->getCount(); i++)
        {
            Entity* e = entities->get(i);
            NotifyManagers(performer, e);
            NotifySystems(performer, e);
        }
        entities->clear();
    }
}

void World::Process()
{
    Check(added, new AddedPerformer());
    Check(changed, new ChangedPerformer());
    Check(disable, new DisabledPerformer());
    Check(enable, new EnabledPerformer());
    Check(deleted, new DeletedPerformer());

    componentManager->Clean();

    for(int i = 0; i <  systemsArray->getCount(); i++)
    {
			EntitySystem* system = systemsArray->get(i);
			if(!system->IsPassive()) {
				system->Process();
			}
    }
}
