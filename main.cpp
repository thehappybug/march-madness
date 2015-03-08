#include "CSVParser.hpp"
#include "Team.hpp"
#include "Game.hpp"
#include "GameDataAdapter.hpp"
#include <iostream>
#include <string>
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

		// Read in all data using the Data Adapter
		// Data is filtered by season.
		std::map<int, Team *> teams;
		GameDataAdapter dataAdapter(seasonName);
		if(dataAdapter.good()) {
			if(dataAdapter.getGamesCount() == 0) {
				cout << "No data for this season." << endl;
				return 0;
			} else {
				teams = dataAdapter.getData();
			}
		} else {
			cout << "ERROR: ";
			cout << dataAdapter.error() << endl;
			return 1;
		}


		Team *champ = NULL;
		float max = -1;

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