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

FinalRecordQuery::FinalRecordQuery()
{
	_numberOfArguments = 1;
	_usageMessage = "Usage: ./madness finalRecord <season> <team name>";
}

// Query for getting the final record of a team in a season
std::vector<std::string> FinalRecordQuery::operator()(std::map<int, Team *> teams, std::vector<std::string> arguments)
{
	assert(arguments.size() == 1);
	std::vector<string> results;

	// Find team
	string teamName = arguments[0];
	auto teamIt = find_if(teams.begin(), teams.end(), [teamName](pair<int, Team *> a) {
		return a.second->name() == teamName;
	});
	
	// If team not found, give error
	if(teamIt == teams.end()) {
		_good = false;
		_error = "Team not in database.\n";
		return results;
	}

	// Get the team's winning and losing count
	Team *team = teamIt->second;
	std::stringstream row("");
	row << team->gamesWon().size() << "-" << (team->gamesPlayed().size() - team->gamesWon().size());
	results.push_back(row.str());
	return results;
}
