#include "BestWinPercentageQuery.hpp"
#include "QueryFactory.hpp"
#include "Game.hpp"
#include "Team.hpp"
#include <algorithm>
#include <string>
#include <sstream>
#include <cassert>
#include <iostream>

using namespace std;

// Register class with the Query Factory
REGISTER_QUERY_CLASS("bestWinPercentage", BestWinPercentageQuery);

BestWinPercentageQuery::BestWinPercentageQuery()
{
	_numberOfArguments = 0;
	_usageMessage = "Usage: ./madness bestWinPercentage <season>";
}

std::vector<std::string> BestWinPercentageQuery::operator()(std::map<int, Team *> teams, std::vector<std::string> arguments)
{
	assert(arguments.size() == 0);

	std::vector<string> results;
	Team *champ = NULL;
	float max = -1;

	// Find element with maximum winning percentage
	for_each(teams.begin(), teams.end(), [&champ, &max](pair<int, Team *> a) {
		if(a.second->winningPercentage() > max) {
			champ = a.second;
			max = a.second->winningPercentage();
		}
	});

	results.push_back(champ->name());
	return results;
}
