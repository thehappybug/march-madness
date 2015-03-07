#ifndef Game_H_
#define Game_H_

#include "Team.hpp"

class Game
{
private:
	Team *_winner;
	Team *_loser;
	int _winningScore;
	int _losingScore;
public:
	Game(Team *winner, Team *loser, int winningScore, int losingScore);
	Team *winner();
	Team *loser();
	bool isWinner(Team *team);
	int winningScore();
	int losingScore();
	~Game();
};

#endif