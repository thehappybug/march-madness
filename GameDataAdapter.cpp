#include "GameDataAdapter.hpp"
#include "Team.hpp"
#include "Game.hpp"
#include "CSVParser.hpp"
#include <map>
#include <cstdlib>
#include <string>
#include <cassert>

using namespace std;

GameDataAdapter::GameDataAdapter(string season)
{
	seasonName = season;
	_gamesCount = 0;
	_good = true;

	CSVParser seasonsData("data/seasons.csv");
	if(seasonsData.fail()) {
		_error = "Failed to open file data/seasons.csv";
		_good = false;
		return;
	}
	seasonsData.skip();

	string seasonId = "";
	while(seasonsData.good()) {
		std::vector<string> row = seasonsData.next();
		if(row.size())
			// cout << row[0] << " " << row[1];
		if(row.size() && row[1] == seasonName) {
			seasonId = row[0];
		}
	}

	if (seasonId == "")
	{
		_error = "Unknown season";
		_good = false;
		return;
	}

	// cout << "Season " << seasonId << endl;


	std::map<int, Team *> teams;

	CSVParser teamsData("data/teams.csv");
	if(teamsData.fail()) {
		_error = "Failed to open file data/teams.csv";
		_good = false;
		return;
	}
	teamsData.skip();

	while(teamsData.good()) {
		std::vector<string> row;
		// cout << "Attempt read" << endl;
		row = teamsData.next();
		// cout << row.size() << endl;
		int id = atoi(row[0].c_str());
		teams[id] = new Team(id, row[1]);
		// cout << id << row[1] << endl;
	}

	CSVParser gamesData("data/regular_tourney_combined_results.csv");
	if(gamesData.fail()) {
		_error = "Failed to open file data/regular_tourney_combined_results.csv";
		_good = false;
		return;
	}
	gamesData.skip();

	// cout << "Reading game data" << endl;

	int gamesCount = 0;
	while(gamesData.good()) {
		std::vector<string> row;
		row = gamesData.next();
		if(row.size() && row[0] == seasonId) {
			// cout << teams[atoi(row[2].c_str())]->name() << " vs " << teams[atoi(row[4].c_str())]->name() << endl;
			Game *game = new Game(teams[atoi(row[2].c_str())], teams[atoi(row[4].c_str())], atoi(row[3].c_str()), atoi(row[5].c_str()), row[6].c_str()[0]);
			assert(game != NULL);
			gamesCount++;
		}
	}

	_gamesCount = gamesCount;
	_teams = teams;
}

std::map<int, Team *> GameDataAdapter::getData()
{
	return _teams;
}

int GameDataAdapter::getGamesCount()
{
	return _gamesCount;
}

bool GameDataAdapter::good()
{
	return _good;
}

std::string GameDataAdapter::error()
{
	return _error;
}

GameDataAdapter::~GameDataAdapter()
{

}

