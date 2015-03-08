#include "RPIChampionQuery.hpp"
#include "QueryFactory.hpp"
#include <algorithm>

using namespace std;

// Register class with the Query Factory
REGISTER_QUERY_CLASS("RPIChampion", RPIChampionQuery);

RPIChampionQuery::RPIChampionQuery() {}

RPIChampionQuery::~RPIChampionQuery() {}

std::vector<std::string> RPIChampionQuery::operator()(std::map<int, Team *> teams, std::vector<std::string> arguments)
{
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
	std::vector<string> v;
	v.push_back(champ->name());
	return v;
}
