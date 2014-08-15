#ifndef GROUPMANAGER_H
#define GROUPMANAGER_H

#include "../Manager.h"
#include "../ImmutableBag.h"
#include <map>
#include <vector>
#include <string>
#include <algorithm>

class GroupManager : public Manager
{
    public:
        GroupManager() : Manager()
		{
			entitiesByGroup = new std::map<std::string, Bag<Entity*>* >();
			groupsByEntity = new std::map<Entity*, std::vector<std::string> >();
		}

        void Initialize() {}

        void Add(Entity* e, std::string group)
        {
            Bag<Entity*>* entities = entitiesByGroup[group];
            if(entities == NULL) {
                entities = new Bag<Entity*>();
                entitiesByGroup[group] = entities;
            }
            entities->add(e);

            std::vector<std::string> groups = groupsByEntity[e];

            groups.push_back(group);
        }

        void Remove(Entity* e, std::string group)
        {
            Bag<Entity*>* entities = entitiesByGroup[group];
            if(entities != NULL) {
                entities->remove(e);
            }

            std::vector<std::string> groups = groupsByEntity[e];
            groups.erase(std::remove(groups.begin(), groups.end(), group), groups.end());

        }

        void RemoveFromAllGroups(Entity* e)
        {
            std::vector<std::string> groups = groupsByEntity[e];
            for(int i = 0; groups.size() > i; i++) {
                Bag<Entity*>* entities = entitiesByGroup[groups[i]];
                if(entities != NULL) {
                    entities->remove(e);
                }
            }

            groups.clear();
        }

        Bag<Entity*>* GetEntities(std::string group)
        {
            Bag<Entity*>* entities = entitiesByGroup[group];
            if(entities == NULL) {
                entities = new Bag<Entity*>();
                entitiesByGroup[group] = entities;
            }
            return entities;
        }

        std::vector<std::string> GetGroups(Entity* e)
        {
            return groupsByEntity[e];
        }

        bool IsInAnyGroup(Entity* e) {
            return groupsByEntity[e].size() > 0;
        }

        bool IsInGroup(Entity* e, std::string group)
        {
            std::vector<std::string> groups = groupsByEntity[e];
            for(int i = 0; groups.size() > i; i++)
            {
                std::string g = groups[i];
                if(group == g || group.compare(g) == 0)
                {
                    return true;
                }
            }
            return false;
        }

        void Deleted(Entity* e) {
            RemoveFromAllGroups(e);
        }

    protected:
    private:
        std::map<std::string, Bag<Entity*>* >* entitiesByGroup;
        std::map<Entity*, std::vector<std::string> >* groupsByEntity;
};

#endif // GROUPMANAGER_H
