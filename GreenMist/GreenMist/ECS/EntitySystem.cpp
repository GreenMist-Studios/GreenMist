#include "EntitySystem.h"

int SystemIndexManager::INDEX = 0;
std::map<const std::type_info*, int> SystemIndexManager::indices = std::map<const std::type_info*, int>();

EntitySystem::EntitySystem(const std::type_info* type, Aspect* as)
{
	actives = new std::vector<Entity*>();
    aspect = as;
    allSet = aspect->GetAllSet();
    exclusionSet = aspect->GetExclusionSet();
    oneSet = aspect->GetOneSet();
    systemIndex = SystemIndexManager::GetIndexFor(type);
    dummy = allSet->none() && oneSet->none(); // This system can't possibly be interested in any entity, so it must be "dummy"
}

void EntitySystem::Check(Entity* e)
{
    if(dummy) {
        return;
    }

    bool contains = e->GetSystemBits()->test(systemIndex);
    bool interested = true; // possibly interested, let's try to prove it wrong.

    std::bitset<BITSIZE>* componentBits = e->GetComponentBits();

    // Check if the entity possesses ALL of the components defined in the aspect.
    if(!allSet->none()) {
        for (int i = 0; i < BITSIZE; i++){
            if(allSet->test(i) && !componentBits->test(i))
            {
                interested = false;
                break;
            }
        }
    }

    // Check if the entity possesses ANY of the exclusion components, if it does then the system is not interested.
    if(!exclusionSet->none() && interested) {
        interested = ! Intersects(exclusionSet,componentBits);
    }

    // Check if the entity possesses ANY of the components in the oneSet. If so, the system is interested.
    if(!oneSet->none()) {
        interested = Intersects(oneSet,componentBits);
    }
    if (interested && !contains) {
        InsertToSystem(e);
    } else if (!interested && contains) {
        RemoveFromSystem(e);
    }
}

void EntitySystem::InsertToSystem(Entity* e)
{
	actives->push_back(e);
    e->GetSystemBits()->set(systemIndex, true);
    Inserted(e);
}

void EntitySystem::RemoveFromSystem(Entity* e) {

	actives->erase(std::find(actives->begin(), actives->end(), e));
    e->GetSystemBits()->set(systemIndex,false);
    Removed(e);
}

void EntitySystem::Deleted(Entity* e)
{
    if(e->GetSystemBits()->test(systemIndex))
    {
        RemoveFromSystem(e);
    }
}

void EntitySystem::Disabled(Entity* e)
{
    if(e->GetSystemBits()->test(systemIndex))
    {
        RemoveFromSystem(e);
    }
}


void EntitySystem::SetPassive(bool pass)
{
    passive = pass;
}

bool EntitySystem::IsPassive()
{
    return passive;
}

