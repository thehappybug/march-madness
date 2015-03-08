#ifndef FINAL_RECORD_QUERY_H
#define FINAL_RECORD_QUERY_H

#include "QueryBase.hpp"
#include <iostream>
using namespace std;

class FinalRecordQuery : public QueryBase
{
public:
	FinalRecordQuery();
    virtual std::vector<std::string> operator()(std::map<int, Team *> teams, std::vector<std::string> arguments);
};
#endif