#ifndef LARGEST_MARGIN_QUERY_H
#define LARGEST_MARGIN_QUERY_H

#include "QueryBase.hpp"
#include <iostream>
using namespace std;

class LargestMarginQuery : public QueryBase
{
public:
    virtual std::vector<std::string> operator()(std::map<int, Team *> teams, std::vector<std::string> arguments);
};
#endif