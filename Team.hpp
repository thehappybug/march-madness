#ifndef Team_H_
#define Team_H_

class Team;

#include "Game.hpp"
#include <vector>
#include <string>

class Team
{
private:
	int _id;
	std::string _name;
	float _owp;
	std::vector<Game *> _gamesWon;
	std::vector<Game *> _gamesPlayed;
public:
	Team(int id, std::string name);
	int id();
	std::string name();
	void addGame(Game *game);
	std::vector<Game *> gamesWon();
	std::vector<Game *> gamesPlayed();
	float winningPercentage();
	float winningPercentageExcluding(Team *excludedTeam);
	float opponentsWinningPercentage();
	float opponentsOpponentsWinningPercentage();
	float ratingsPercentageIndex();
	~Team();
};

#endif