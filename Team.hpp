#ifndef Team_H_
#define Team_H_

class Team;

#include "Game.hpp"
#include <vector>
#include <string>

/**
 * Represents one Team
 *
 * Provides useful functions for calculations
 * of team performance too. Results depends on
 * the correctness of games data.
 */
class Team
{
public:
	Team(int id, std::string name);
	int id();
	std::string name();
	void addGame(Game *game);
	std::vector<Game *> gamesWon();
	std::vector<Game *> gamesPlayed();
	float winningPercentage();
	float weightedWinningPercentage();
	float winningPercentageExcluding(Team *excludedTeam);
	float opponentsWinningPercentage();
	float opponentsOpponentsWinningPercentage();
	float ratingsPercentageIndex();
	~Team();
private:
	int _id;
	std::string _name;
	float _owp;
	float _oowp;
	float _rpi;
	std::vector<Game *> _gamesWon;
	std::vector<Game *> _gamesPlayed;
};

#endif