#include "RPIChampionQuery.hpp"
#include "QueryFactory.hpp"
#include <algorithm>
#include <cassert>

using namespace std;

// Register class with the Query Factory
REGISTER_QUERY_CLASS("rpiChampion", RPIChampionQuery);

std::vector<std::string> RPIChampionQuery::operator()(std::map<int, Team *> teams, std::vector<std::string> arguments)
{
	assert(arguments.size() == 0);

	Team *champ = NULL;
	float max = -1;

	for_each(teams.begin(), teams.end(), [&champ, &max](pair<int, Team *> a) {
		if(a.second->ratingsPercentageIndex() > max) {
			champ = a.second;
			max = a.second->ratingsPercentageIndex();
		}
	});

	std::vector<string> v;
	v.push_back(champ->name());
	return v;
}
