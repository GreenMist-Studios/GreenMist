#ifndef PLAYERMANAGER_H
#define PLAYERMANAGER_H

#include "../Manager.h"
#include "../ImmutableBag.h"
#include <map>
#include <vector>
#include <string>
#include <algorithm>
class PlayerManager : public Manager
{
    public:
        PlayerManager() 
		{
			playerByEntity = new std::map<Entity*, std::string>();
			entitiesByPlayer = new std::map<std::string, Bag<Entity*>*>();
		}

        virtual ~PlayerManager() {}

        void Initialize() {}

        void SetPlayer(Entity* e, std::string player)
        {
            if (playerByEntity->find(e) == playerByEntity->end())
                playerByEntity->insert(std::pair<Entity*,std::string>(e,player));
            else
                playerByEntity[e] = player;

            Bag<Entity*>* entities = entitiesByPlayer[player];
            if(entities == NULL) {
                entities = new Bag<Entity*>();
                entitiesByPlayer[player] = entities;
            }
            entities->add(e);
        }

        ImmutableBag<Entity*>* GetEntitiesOfPlayer(std::string player)
        {
            Bag<Entity*>* entities = entitiesByPlayer[player];
            if(entities == NULL) {
                entities = new Bag<Entity*>();
            }
            return entities;
        }

        void RemoveFromPlayer(Entity* e)
        {
            if(playerByEntity->find(e) != playerByEntity->end())
            {
                std::string player = playerByEntity[e];
                Bag<Entity*>* entities = entitiesByPlayer[player];
                if(entities != NULL) {
                    entities->remove(e);
                }
                playerByEntity->erase(e);
            }
        }

        std::string GetPlayer(Entity* e)
        {
            if(playerByEntity->find(e) != playerByEntity->end())
            {
                return playerByEntity[e];
            }
            return "";
        }

        void Deleted(Entity* e)
        {
            RemoveFromPlayer(e);
        }

    protected:
    private:
        std::map<Entity*, std::string>* playerByEntity;
        std::map<std::string, Bag<Entity*>* >* entitiesByPlayer;
};

#endif // PLAYERMANAGER_H
