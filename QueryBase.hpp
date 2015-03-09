#ifndef QUERY_BASE_H
#define QUERY_BASE_H

#include <map>
#include <vector>
#include <string>
#include "Team.hpp"

/**
 * Base class for Queries
 * 
 * Make new queries by inheriting this class.
 * 
 * Inherited classes should set the protected variables in
 * their ctors. Also, they should register themselves with
 * the QueryFactory using the macro:
 * 		REGISTER_QUERY_CLASS("queryName", queryClassName);
 */
class QueryBase
{
public:
	// No. of arguments needed by query to run
	unsigned int numberOfArguments()
	{
		return _numberOfArguments;
	}

	// Usage message for query
	std::string usageMessage()
	{
		return _usageMessage;
	}

	// Is the query execution status ok?
	bool good()
	{
		return _good;
	}

	// Get error message
	std::string error()
	{
		return _error;
	}

	// Execute the query
    virtual std::vector<std::string> operator()(std::map<int, Team *> teams, std::vector<std::string> arguments) = 0;
protected:
	bool _good = true;
	std::string _error;
	unsigned int _numberOfArguments;
	std::string _usageMessage;
};

#endif