#include "Team.hpp"
#include "Game.hpp"
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>

using namespace std;

Team::Team(int id, string name)
{
	_id = id;
	_name = name;
	_owp = -1;
	_rpi = -1;
}

int Team::id()
{
	return _id;
}

string Team::name()
{
	return _name;
}

void Team::addGame(Game *game)
{
	if(game->isWinner(this)) {
		// cout << game->winner()->name() << ", " << game->loser()->name() << endl;
		_gamesWon.push_back(game);
	}
	_gamesPlayed.push_back(game);
	_owp = -1;
	_rpi = -1;
}

std::vector<Game *> Team::gamesWon()
{
	return _gamesWon;
}

std::vector<Game *> Team::gamesPlayed()
{
	return _gamesPlayed;
}

float Team::winningPercentage()
{
	// cout << _gamesPlayed.size();
	// cout << _gamesWon.size();
	// return (float)_gamesWon.size() / (float)_gamesPlayed.size() ;
	float won = 0;
	float played = 0;

	for (std::vector<Game *>::iterator i = _gamesPlayed.begin(); i != _gamesPlayed.end(); ++i)
	{
		float sc = 0;
		if((*i)->isWinner(this)) {
			if ((*i)->turf() == 'A')
			{
				won += 	1.4;
				played += 	1.4;
			} else if (((*i)->turf() == 'H')) {
				won += 	0.6;
				played += 	0.6;				
			} else {
				won += 	1;
				played += 	1;								
			}
		
		} else {
			if ((*i)->turf() == 'A')
			{
				played += 	1.4;
			} else if (((*i)->turf() == 'H')) {
				played += 	0.6;				
			} else {
				played += 	1;								
			}			
		}
	}
	return won/played;
}

float Team::winningPercentageExcluding(Team *excludedTeam)
{
	float won = 0;
	float played = 0;
	for (std::vector<Game *>::iterator i = _gamesPlayed.begin(); i != _gamesPlayed.end(); ++i)
	{
		// cout << (*i)->winner()->name() << ", " << (*i)->loser()->name();
		if(!((*i)->isPlayer(excludedTeam))) {
			played++;
			// cout << " Played ";
			if(((*i)->isWinner(this))) {
				won++;
				// cout << " Won ";
			}
		}
		// cout << endl;
	}
	return played ? won / played  : 0;
}

float Team::opponentsWinningPercentage()
{
	if(_owp != -1)
		return _owp;
	std::vector<float> wps;
	wps.resize(_gamesPlayed.size());
	std::transform(_gamesPlayed.begin(), _gamesPlayed.end(), wps.begin(), [this](Game *game) { 
		// cout << game->otherPlayer(this)->name() << ", " << this->name() << " " << game->otherPlayer(this)->winningPercentageExcluding(this) << endl; 
		return game->otherPlayer(this)->winningPercentageExcluding(this);
	});
	float sum_wps = std::accumulate(wps.begin(), wps.end(), 0.0);
	// cout << sum_wps << endl;
	_owp = sum_wps / wps.size() ;
	return _owp;
}

float Team::opponentsOpponentsWinningPercentage()
{
	std::vector<float> owps;
	owps.resize(_gamesPlayed.size());
	std::transform(_gamesPlayed.begin(), _gamesPlayed.end(), owps.begin(), [this](Game *game) { 
		return game->otherPlayer(this)->opponentsWinningPercentage();
	});
	float sum_wps = std::accumulate(owps.begin(), owps.end(), 0.0);
	return sum_wps / owps.size() ;
}

float Team::ratingsPercentageIndex()
{
	if (_rpi != -1)
	{
		return _rpi;
	}
	_rpi = this->winningPercentage() * 0.25	+
		   this->opponentsWinningPercentage() * 0.5 +
		   this->opponentsOpponentsWinningPercentage() * 0.25;
    return _rpi;
}

Team::~Team()
{

}

