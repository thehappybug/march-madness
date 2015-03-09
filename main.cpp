#include "Team.hpp"
#include "Game.hpp"
#include "GameDataAdapter.hpp"
#include "QueryFactory.hpp"
#include "QueryBase.hpp"
#include <iostream>
#include <string>
#include <map>

using namespace std;

int main(int argc, char const *argv[])
{
	// Check for missing query type argument
	if(argc < 2) {
		cout << "Incorrect arguments." << endl;
		cout << "./madness <command> <arguments, ...>" << endl;
		return 1;
	}

	string queryType = string(argv[1]);

	// Create the query of a specific query type using the factory
	auto query = QueryFactory::Instance()->Create(queryType);
	if(query == nullptr) {
		cout << "Unknown query type" << endl;
		return 0;
	}

	// Package arguments needed by the query into a vector
	std::vector<string> arguments;
	if(argc > 3) {
		arguments = std::vector<string>(argv+3, argv+argc);
	}

	// Check correct number of arguments given match query's
	if((int)query->numberOfArguments() != (argc-3)) {
		cout << query->usageMessage();
		return 0;
	}

	// Read in all data set using the data adapter 
	// (filtered by season)
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

	// Run the query created earlier on the data set
	auto results = (*query)(teams, arguments);

	// Check for query error
	if(query->good()) {
		// Display results
		for (std::vector<string>::iterator i = results.begin(); i != results.end(); ++i)
			cout << *i << endl;		
	} else {
		// Show error message
		cout << "There was an error running the query." << endl;
		cout << query->error() << endl;
		return 1;
	}

	return 0;
}