#ifndef ENTITYSYSTEMS_H
#define ENTITYSYSTEMS_H

#include <bitset>
#include <algorithm>
#include <map>
#include <typeinfo>
#include <vector>
#include "ImmutableBag.h"
#include "EntityObserver.h"
#include "Entity.h"
#include "Aspect.h"
#include "World.h"

class SystemIndexManager
{
    public:
		static int GetIndexFor(const std::type_info* es)
		{
			int index = indices[es];
			if(index == 0) {
				index = INDEX++;
				indices[es] = index;
			}
			return index;
		}

    private:
        static int INDEX;
		static std::map<const std::type_info*, int> indices;
};

class EntitySystem : public EntityObserver
{
    public:
        EntitySystem(const std::type_info* type,Aspect* aspect);

        virtual void Initialize(){}

        virtual void Begin(){}

        void Process()
        {
            if(CheckProcessing())
            {
                Begin();
                ProcessEntities(actives);
                End();
            }
        }

        virtual void End(){}
        virtual void ProcessEntities(std::vector<Entity*>* entities){}
        virtual bool CheckProcessing(){ return false;}

        virtual void Inserted(Entity* e) {}
        virtual void Removed(Entity* e) {}

        void Check(Entity* e);

        void InsertToSystem(Entity* e);
        void RemoveFromSystem(Entity* e);

        void Added(Entity* e)
        {
            Check(e);
        }
        void Changed(Entity* e)
        {
            Check(e);
        }

        void Deleted(Entity* e);
        void Disabled(Entity* e);

        void Enabled(Entity* e)
        {
            Check(e);
        }

        void SetWorld(World* w) {
            world = w;
        }

        void SetPassive(bool passive);
        bool IsPassive();

		std::vector<Entity*>* GetActives() {
            return actives;
        }
    protected:
        int systemIndex;

        World* world;
        Aspect* aspect;
		std::vector<Entity*>* actives;

        std::bitset<BITSIZE>* allSet;
        std::bitset<BITSIZE>* exclusionSet;
        std::bitset<BITSIZE>* oneSet;

        bool passive;
        bool dummy;
};

inline bool Intersects(std::bitset<BITSIZE>* one, std::bitset<BITSIZE>* two)
{
    for (int i = 0; i < BITSIZE; i++)
    {
        if (one->test(i) && two->test(i))
            return true;
    }
    return false;
}

#endif // ENTITYSYSTEMS_H
