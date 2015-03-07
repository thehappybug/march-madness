#include "Team.h"
#include "Game.h"

Game::Game(Team *winner, Team *loser, int winningScore, int losingScore)
{
	_winner = winner;
	_loser = loser;
	_winningScore = winningScore;
	_losingScore = losingScore; 
}

Team *Game::winner()
{
	return _winner;
}

Team *Game::loser()
{
	return _loser;
}

bool Game::isWinner(Team *)
{
	if(team->id() == _winner->id())
		return true;
	else
		return false;
}

int Game::winningScore()
{
	return _winningScore;
}

int Game::losingScore()
{
	return _losingScore;
}

Game::~Game()
{

}
