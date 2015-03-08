#include "CSVParser.hpp"
#include "Team.hpp"
#include "Game.hpp"
#include "GameDataAdapter.hpp"
#include "QueryFactory.hpp"
#include "QueryBase.hpp"
#include "RPIChampionQuery.hpp"
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

	string queryType = string(argv[1]);

	if(queryType == "rpiChampion") {
		if(argc < 3) {
			cout << "Usage: ./madness rpiChampion <season>" << endl;
			return 1;
		}
	}

	// Create the query
	auto query = QueryFactory::Instance()->Create(queryType);
	if(query == nullptr) {
		cout << "Unknown query type" << endl;
		return 0;
	}

	// Package arguments into a vector
	std::vector<string> arguments;
	if(argc > 3) {
		arguments = std::vector<string>(argv+3, argv+argc);
	}

	// Read in all data using the Data Adapter (filtered by season)
	string seasonName(argv[2]);
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

	// Run query and Display the results
	auto results = (*query)(teams, arguments);
	for (std::vector<string>::iterator i = results.begin(); i != results.end(); ++i)
		cout << *i << endl;

	return 0;
}