#include "EntityManager.h"

EntityManager::EntityManager()
{
    entities = new Bag<Entity*>();
	disabled = new std::bitset<BITSIZE>();
    disabled->reset();
    identifierPool = new IdentifierPool();

    _active = 0;
    _created = 0;
    _added = 0;
    _deleted = 0;
}

Entity* EntityManager::CreateEntityInstance()
{
    Entity* e = new Entity(world, identifierPool->checkOut());
    _created++;
    return e;
}

void EntityManager::Added(Entity* e)
{
    _active++;
    _added++;
    entities->set(e->GetId(), e);
}

void EntityManager::Enabled(Entity* e)
{
    disabled->set(e->GetId(), false);
}

void EntityManager::Disabled(Entity* e)
{
    disabled->set(e->GetId(), true);
}

void EntityManager::Deleted(Entity* e)
{
    entities->set(e->GetId(), NULL);

    disabled->set(e->GetId(), false);

    identifierPool->checkIn(e->GetId());

    _active--;
    _deleted++;
}

bool EntityManager::IsActive(int entityId)
{
    return entities->get(entityId) != NULL;
}

Entity* EntityManager::GetEntity(int entityId)
{
    return entities->get(entityId);
}

bool EntityManager::IsEnabled(int entityId)
{
    return !disabled->test(entityId);
}
