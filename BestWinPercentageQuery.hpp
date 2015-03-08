#ifndef BEST_WIN_PERCENTAGE_QUERY_H
#define BEST_WIN_PERCENTAGE_QUERY_H

#include "QueryBase.hpp"
#include <iostream>
using namespace std;

class BestWinPercentageQuery : public QueryBase
{
public:
    virtual std::vector<std::string> operator()(std::map<int, Team *> teams, std::vector<std::string> arguments);
};
#endif