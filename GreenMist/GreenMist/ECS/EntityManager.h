#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include <bitset>
#include <vector>
#include "ImmutableBag.h"
#include "Manager.h"
#include "Bitsize.h"
#include "Entity.h"
#include "World.h"

class IdentifierPool {
public:

        IdentifierPool() {
			ids = new std::vector<int>();
			nextAvailableId = 0;
		}

		int checkOut() {
			if(ids->size() > 0)
            {
                int val = (*ids->end());
				ids->pop_back();
                return val;
			}
			return nextAvailableId++;
		}

		void checkIn(int id) {
			ids->push_back(id);
		}

private:
        std::vector<int>* ids;
		long nextAvailableId;
};


class EntityManager : public Manager
{
    public:
        EntityManager();

        Entity* CreateEntityInstance();

        void Added(Entity* e);
        void Enabled(Entity* e);
        void Disabled(Entity* e);
        void Deleted(Entity* e);

        bool IsActive(int entityId);
        Entity*GetEntity(int entityId);

        bool IsEnabled(int entityId);

        int GetActiveEntityCount()
        {
            return _active;
        }

        long GetTotalCreated()
        {
            return _created;
        }

        long GetTotalAdded()
        {
            return _added;
        }

        long GetTotalDeleted()
        {
            return _deleted;
        }
    protected:
    private:
        Bag<Entity*>* entities;
        std::bitset<BITSIZE>* disabled;
        IdentifierPool* identifierPool;
        int _active;
        long _added;
        long _created;
        long _deleted;

};

#endif // ENTITYMANAGER_H
