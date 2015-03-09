#ifndef BEST_WIN_PERCENTAGE_QUERY_H
#define BEST_WIN_PERCENTAGE_QUERY_H

#include "QueryBase.hpp"
#include <iostream>
using namespace std;

/**
 * Find the team with the best win percentage in a season.
 */
class BestWinPercentageQuery : public QueryBase
{
public:
	BestWinPercentageQuery();
    virtual std::vector<std::string> operator()(std::map<int, Team *> teams, std::vector<std::string> arguments);
};
#endif