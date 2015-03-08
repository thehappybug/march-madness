#include "FinalRecordQuery.hpp"
#include "QueryFactory.hpp"
#include "Game.hpp"
#include "Team.hpp"
#include <algorithm>
#include <string>
#include <sstream>
#include <cassert>

using namespace std;

// Register class with the Query Factory
REGISTER_QUERY_CLASS("finalRecord", FinalRecordQuery);

std::vector<std::string> FinalRecordQuery::operator()(std::map<int, Team *> teams, std::vector<std::string> arguments)
{
	assert(arguments.size() == 1);

	// Find team
	string teamName = arguments[0];
	auto teamIt = find_if(teams.begin(), teams.end(), [teamName](pair<int, Team *> a) {
		return a.second->name() == teamName;
	});
	assert(teamIt != teams.end());

	// Get the team's winning and losing count
	std::vector<string> results;
	Team *team = teamIt->second;
	std::stringstream row("");
	row << team->gamesWon().size() << "-" << (team->gamesPlayed().size() - team->gamesWon().size());
	results.push_back(row.str());
	return results;
}
