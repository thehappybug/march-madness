#ifndef Game_H_
#define Game_H_

class Game;

#include "Team.hpp"

/**
 * Represents one Game played by 2 teams
 *
 * Creating a new game will automatically register
 * the created game with the playing Teams as well
 * using the addGame(Game *) function of Team class.
 */
class Game
{
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
private:
	Team *_winner;
	Team *_loser;
	int _winningScore;
	int _losingScore;
	char _turf;
};

#endif