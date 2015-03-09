#ifndef RPI_CHAMPION_QUERY_H
#define RPI_CHAMPION_QUERY_H

#include "QueryBase.hpp"
#include <iostream>
using namespace std;

/**
 * Query for finding the teams with the highest RPI in a season
 */
class RPIChampionQuery : public QueryBase
{
public:
	RPIChampionQuery();
    virtual std::vector<std::string> operator()(std::map<int, Team *> teams, std::vector<std::string> arguments);
};
#endif