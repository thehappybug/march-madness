#ifndef Game_H_
#define Game_H_

class Game;

#include "Team.hpp"

class Game
{
private:
	Team *_winner;
	Team *_loser;
	int _winningScore;
	int _losingScore;
	char _turf;
public:
	Game(Team *winner, Team *loser, int winningScore, int losingScore, char turf);
	Team *winner();
	Team *loser();
	bool isWinner(Team *team);
	bool isPlayer(Team *team);
	Team *otherPlayer(Team *team);
	int winningScore();
	int losingScore();
	char turf();
	~Game();
};

#endif