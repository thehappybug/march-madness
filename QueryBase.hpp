#ifndef QUERY_BASE_H
#define QUERY_BASE_H

#include <map>
#include <vector>
#include <string>
#include "Team.hpp"

class QueryBase
{
public:
	unsigned int numberOfArguments()
	{
		return _numberOfArguments;
	}

	std::string usageMessage()
	{
		return _usageMessage;
	}

	bool good()
	{
		return _good;
	}

	std::string error()
	{
		return _error;
	}

    virtual std::vector<std::string> operator()(std::map<int, Team *> teams, std::vector<std::string> arguments) = 0;
protected:
	bool _good = true;
	std::string _error;
	unsigned int _numberOfArguments;
	std::string _usageMessage;
};

#endif