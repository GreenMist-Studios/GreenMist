#ifndef TAGMANAGER_H
#define TAGMANAGER_H

#include "../Manager.h"
#include "../ImmutableBag.h"
#include <map>
#include <vector>
#include <string>
#include <algorithm>

class TagManager : public Manager
{
    public:
        TagManager()
		{
			entitiesByTag = new std::map<std::string, Entity*>();
			tagsByEntity = new std::map<Entity*, std::string >();
		}

    void Register(std::string tag, Entity* e)
    {
        if (!IsRegistered(tag))
        {
            entitiesByTag->insert(std::pair<std::string, Entity*>(tag, e));
            tagsByEntity->insert(std::pair<Entity*, std::string>(e, tag));
        }
        else
        {
            entitiesByTag[tag] = e;
            tagsByEntity[e] = tag;
        }
	}

    void Unregister(std::string tag)
    {
        if (IsRegistered(tag))
        {
            Entity* e = entitiesByTag[tag];
            entitiesByTag->erase(tag);
            tagsByEntity->erase(e);
        }
	}

    bool IsRegistered(std::string tag) {
		return entitiesByTag->find(tag) != entitiesByTag->end();
	}

	Entity* GetEntity(std::string tag) {
		return entitiesByTag[tag];
	}

    std::vector<std::string> GetRegisteredTags() {
        std::vector<std::string> tags;

        for (std::map<Entity* ,std::string>::iterator it = tagsByEntity->begin(); it != tagsByEntity->end(); it++)
        {
            tags.push_back(it->second);
        }
		return tags;
	}

    void Deleted(Entity* e)
    {
        if (tagsByEntity->find(e) != tagsByEntity->end())
        {
            std::string removedTag = tagsByEntity[e];
            tagsByEntity->erase(e);
            entitiesByTag->erase(removedTag);
		}
	}

    private:
        std::map<std::string, Entity*>* entitiesByTag;
        std::map<Entity*, std::string >* tagsByEntity;
};

#endif // TAGMANAGER_H
