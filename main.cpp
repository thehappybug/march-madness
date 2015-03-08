#include "CSVParser.hpp"
#include "Team.hpp"
#include "Game.hpp"
#include <iostream>
#include <string>
#include <cstdlib>
#include <algorithm>
#include <map>

using namespace std;

int main(int argc, char const *argv[])
{
	if(argc < 2) {
		cout << "Incorrect arguments." << endl;
		cout << "./madness <command> <arguments, ...>" << endl;
		return 1;
	}

	string command = string(argv[1]);

	if(command == "rpiChampion") {
		if(argc < 3) {
			cout << "Usage: ./madness rpiChampion <season>" << endl;
			return 1;
		}

		string seasonName(argv[2]);
		string seasonId = "";

		CSVParser seasonsData("data/seasons.csv");
		if(seasonsData.fail()) {
			cout << "Failed to open file data/seasons.csv" << endl;
			return 1;
		}
		seasonsData.skip();

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
			cout << "Unknown season" << endl;
			return 1;
		}

		// cout << "Season " << seasonId << endl;


		std::map<int, Team *> teams;

		CSVParser teamsData("data/teams.csv");
		if(teamsData.fail()) {
			cout << "Failed to open file data/teams.csv" << endl;
			return 1;
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
			cout << "Failed to open file data/regular_tourney_combined_results.csv" << endl;
			return 1;
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
				gamesCount++;
			}
		}

		if(gamesCount == 0) {
			cout << "No data for this season." << endl;
			return 0;
		}

		Team *champ = NULL;
		float max = -1;
		// cout << champ->name() << endl;

		for_each(teams.begin(), teams.end(), [&champ, &max](pair<int, Team *> a) {
			// cout << a.second->ratingsPercentageIndex() ;
			// cout << champ->ratingsPercentageIndex() ;
			// cout << a.second->name() << " " << a.second->ratingsPercentageIndex() << ", " << a.second->winningPercentage() << ", " << a.second->opponentsWinningPercentage() << ", " << a.second->opponentsOpponentsWinningPercentage() << endl;
			if(a.second->ratingsPercentageIndex() > max) {
				champ = a.second;
				max = a.second->ratingsPercentageIndex();
				// cout << a.second->name() << endl;
			}
		});

		// cout << champ->name() << " " << champ->ratingsPercentageIndex() << endl;
		cout << champ->name()<< endl;
	}
	return 0;
}