#include "ListGamesQuery.hpp"
#include "QueryFactory.hpp"
#include "Game.hpp"
#include "Team.hpp"
#include <algorithm>
#include <string>
#include <sstream>
#include <cassert>

using namespace std;

// Register class with the Query Factory
REGISTER_QUERY_CLASS("list", ListGamesQuery);

std::vector<std::string> ListGamesQuery::operator()(std::map<int, Team *> teams, std::vector<std::string> arguments)
{
	assert(arguments.size() == 1);

	string teamName = arguments[0];

	// Find team
	auto teamIt = find_if(teams.begin(), teams.end(), [teamName](pair<int, Team *> a) {
		return a.second->name() == teamName;
	});

	assert(teamIt != teams.end());

	// Build the results
	Team *team = teamIt->second;
	std::vector<string> results;
	std::vector<Game *> gamesPlayed = team->gamesPlayed();
	for (std::vector<Game *>::iterator i = gamesPlayed.begin(); i != gamesPlayed.end(); i++)
	{
		std::stringstream row("");
		row << (((*i)->isWinner(team)) ? "W " : "L ");
		row << (*i)->otherPlayer(team)->name() << " ";
		row << (((*i)->isWinner(team)) ? (*i)->winningScore() : (*i)->losingScore()) << "-";
		row << (!((*i)->isWinner(team)) ? (*i)->winningScore() : (*i)->losingScore());
		results.push_back(row.str());
	}

	return results;
}
