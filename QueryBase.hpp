#ifndef QUERY_BASE_H
#define QUERY_BASE_H

#include <map>
#include <vector>
#include <string>
#include "Team.hpp"

class QueryBase
{
public:
    virtual std::vector<std::string> operator()(std::map<int, Team *> teams, std::vector<std::string> arguments) = 0;
};

#endif