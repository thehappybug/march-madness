#include "Team.hpp"
#include "Game.hpp"
#include <iostream>

using namespace std;

Game::Game(Team *winner, Team *loser, int winningScore, int losingScore, char turf)
{
	_winner = winner;
	_loser = loser;
	_winningScore = winningScore;
	_losingScore = losingScore; 
	_turf = turf;
	winner->addGame(this);
	loser->addGame(this);
}

Team *Game::winner()
{
	return _winner;
}

Team *Game::loser()
{
	return _loser;
}

bool Game::isWinner(Team *team)
{
	// cout << "Compare " << team->id() << ", " << _winner->id() << endl;
	if(team->id() == _winner->id())
		return true;
	else
		return false;
}

bool Game::isPlayer(Team *team)
{
	if(team->id() == _winner->id() || team->id() == _loser->id())
		return true;
	else
		return false;
}

Team *Game::otherPlayer(Team *team)
{
	if(team->id() == _winner->id())
		return _loser;
	else
		return _winner;
}

int Game::winningScore()
{
	return _winningScore;
}

int Game::losingScore()
{
	return _losingScore;
}

char Game::turf()
{
	return _turf;
}

Game::~Game()
{

}
