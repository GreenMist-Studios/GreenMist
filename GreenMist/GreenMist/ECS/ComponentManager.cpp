#include "ComponentManager.h"

Bag<Component*> ComponentManager::GetComponentsFor(Entity* e, Bag<Component*> fillVector)
{
    std::bitset<BITSIZE>* componentBits = e->GetComponentBits();

    for (int i = 0; i < BITSIZE; i++)
    {
        if (componentBits->test(i))
            fillVector.add(componentsByType->get(i)->get(e->GetId()));
    }

    return fillVector;
}

void ComponentManager::RemoveComponentsOfEntity(Entity* e)
{
    std::bitset<BITSIZE>* componentBits = e->GetComponentBits();
    for (int i = 0; i < BITSIZE; i++)
    {
        if (componentBits->test(i))
        {
            componentsByType->get(i)->set(e->GetId(),NULL);
        }
    }
    componentBits->reset();
}

void ComponentManager::AddComponent(Entity* e, ComponentType* type, Component* component)
{
    Bag<Component*>* components = componentsByType->get(type->GetIndex());

    if (components == NULL)
    {
        components = new Bag<Component*>();
        componentsByType->set(type->GetIndex(),components);
    }

    components->set(e->GetId(), component);
    e->GetComponentBits()->set(type->GetIndex());
}

void ComponentManager::RemoveComponent(Entity* e, ComponentType* type)
{
    if(e->GetComponentBits()->test(type->GetIndex()))
    {
        componentsByType->get(type->GetIndex())->set(e->GetId(), NULL);
        e->GetComponentBits()->set(type->GetIndex(), false);
    }
}


Bag<Component*>* ComponentManager::GetComponentsByType(ComponentType* type)
{
    Bag<Component*>* components = componentsByType->get(type->GetIndex());
    if(components == NULL) {
        components = new Bag<Component*>();
        componentsByType->set(type->GetIndex(), components);
    }

    return components;
}

Component* ComponentManager::GetComponent(Entity* e, ComponentType* type)
{
    Bag<Component*>* components = componentsByType->get(type->GetIndex());
    if(components != NULL) {
        return components->get(e->GetId());
    }
    return NULL;
}

void ComponentManager::Deleted(Entity* e)
{
    deleted.add(e);
}

void ComponentManager::Clean()
{
    if(deleted.getCount() > 0)
    {
        for(int i = 0; deleted.getCount() > i; i++)
        {
            RemoveComponentsOfEntity(deleted.get(i));
        }
        deleted.clear();
    }
}
