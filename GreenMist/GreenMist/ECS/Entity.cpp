#include "Entity.h"

Entity::Entity(World* w, int ID)
{
    //ctor
    componentBits = new std::bitset<BITSIZE>();
    systemBits = new std::bitset<BITSIZE>();

    world = w;
    id = ID;
    entityManager = world->GetEntityManager();
    componentManager = world->GetComponentManager();

    Reset();
}

Entity* Entity::Work(Component* component, ComponentType* type)
{
    return AddComponent(component, type);
}

Entity* Entity::AddComponent(Component* component, ComponentType* type)
{
    componentManager->AddComponent(this, type, component);
    return this;
}

Entity* Entity::RemoveComponent(Component* component)
{
    RemoveComponent(&typeid(component));
    return this;
}

Entity* Entity::RemoveComponent(ComponentType* type)
 {
    componentManager->RemoveComponent(this, type);
    return this;
}

Entity* Entity::RemoveComponent(const std::type_info* type)
{
    RemoveComponent(ComponentType::GetTypeFor(type));
    return this;
}

bool Entity::IsActive() {
    return entityManager->IsActive(id);
}

bool Entity::IsEnabled() {
    return entityManager->IsEnabled(id);
}

Component* Entity::GetComponent(ComponentType* type)
{
    return componentManager->GetComponent(this, type);
}

Component* Entity::GetComponent(const std::type_info* type)
{
    return componentManager->GetComponent(this, ComponentType::GetTypeFor(type));
}

template <class T>
T Entity::GetComponent(T null)
{
    return (T) GetComponent(ComponentType::GetTypeFor(&typeid(null)));
}

Bag<Component*> Entity::GetComponents(Bag<Component*> fillBag)
{
    return componentManager->GetComponentsFor(this, fillBag);
}

void Entity::AddToWorld()
{
    world->AddEntity(this);
}

void Entity::ChangedInWorld()
{
    world->ChangedEntity(this);
}

void Entity::DeleteFromWorld()
{
    world->DeleteEntity(this);
}

void Entity::Enable()
{
    world->Enable(this);
}

void  Entity::Disable()
{
    world->Disable(this);
}
