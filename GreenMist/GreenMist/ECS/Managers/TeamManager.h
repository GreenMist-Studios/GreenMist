#ifndef TEAMMANAGER_H
#define TEAMMANAGER_H

#include "../Manager.h"
#include "../ImmutableBag.h"
#include <map>
#include <vector>
#include <string>
#include <algorithm>

class TeamManager : public Manager
{
    public:
        TeamManager() 
		{
			teamByPlayer = new std::map<std::string, std::string >();

		}

        void Initialize() {}

        std::string GetTeam(std::string player)
        {
            return teamByPlayer[player];
        }

        void setTeam(std::string player, std::string team)
        {
            RemoveFromTeam(player);

            teamByPlayer->insert(std::pair<std::string,std::string>(player, team));

            std::vector<std::string> players = playersByTeam[team];
            if(!players.empty())
            {
                playersByTeam->insert(std::pair<std::string,std::vector<std::string> > (team, players));
            }
            players.push_back(player);
        }

        std::vector<std::string> GetPlayers(std::string team)
        {
            return playersByTeam[team];
        }

        void RemoveFromTeam(std::string player)
        {
            if(teamByPlayer->find(player) != teamByPlayer->end())
            {
                std::string team = teamByPlayer[player];
                std::vector<std::string> players = playersByTeam[team];

                std::vector<std::string>::iterator i = std::remove(players.begin(), players.end(), team);

                if (i != players.end())
                    players.erase(i);

                teamByPlayer->erase(player);
            }
        }
    private:
        std::map<std::string, std::vector<std::string> >* playersByTeam;
        std::map<std::string, std::string >* teamByPlayer;
};

#endif // TEAMMANAGER_H
