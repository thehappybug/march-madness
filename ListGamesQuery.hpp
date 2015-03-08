#ifndef LIST_QUERY_H
#define LIST_QUERY_H

#include "QueryBase.hpp"
#include <iostream>
using namespace std;

class ListGamesQuery : public QueryBase
{
public:
	ListGamesQuery();
    virtual std::vector<std::string> operator()(std::map<int, Team *> teams, std::vector<std::string> arguments);
};
#endif