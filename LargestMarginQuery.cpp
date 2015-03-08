#include "LargestMarginQuery.hpp"
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
REGISTER_QUERY_CLASS("largestMargin", LargestMarginQuery);

std::vector<std::string> LargestMarginQuery::operator()(std::map<int, Team *> teams, std::vector<std::string> arguments)
{
	assert(arguments.size() == 0);

	std::vector<string> results;
	Team *champ = NULL;
	float max = -1;

	// Find element with maximum winning margin
	for_each(teams.begin(), teams.end(), [&champ, &max](pair<int, Team *> a) {
		double margin = 0;
		Team *team = a.second;
		auto gamesPlayed = team->gamesPlayed();
		if(gamesPlayed.size()) {
			pair<double, double> init(0.0, 0.0);
			// Sum the points gained and points allowed
			auto scores = accumulate(gamesPlayed.begin(), gamesPlayed.end(), init, [team](pair<double, double> running, Game *game) {
				running.first += (game->isWinner(team) ? game->winningScore() : game->losingScore());
				running.second += (!game->isWinner(team) ? game->winningScore() : game->losingScore());
				return running;
			});
			margin = (scores.first - scores.second)/gamesPlayed.size();			
		}
		if(margin > max) {
			champ = a.second;
			max = margin;
		}
	});

	results.push_back(champ->name());
	return results;
}
