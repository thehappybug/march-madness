#ifndef LARGEST_MARGIN_QUERY_H
#define LARGEST_MARGIN_QUERY_H

#include "QueryBase.hpp"
#include <iostream>
using namespace std;

/**
 * Query for finding the team with the largest margin of victory in a season
 */
class LargestMarginQuery : public QueryBase
{
public:
	LargestMarginQuery();
    virtual std::vector<std::string> operator()(std::map<int, Team *> teams, std::vector<std::string> arguments);
};
#endif