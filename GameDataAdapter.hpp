#ifndef GameDataAdapter_H_
#define GameDataAdapter_H_

#include <string>
#include <map>
#include "Team.hpp"

/**
 * Data adapter
 *
 * Converts data read from CSVParser into objects
 * of Team and Game classes. Resulting data resembles
 * something like a graph.
 */
class GameDataAdapter
{
public:
	GameDataAdapter(std::string season);
	std::map<int, Team *> getData();
	int getGamesCount();
	bool good();
	std::string error();
	~GameDataAdapter();

private:
	int _gamesCount;
	std::string seasonName;
	std::map<int, Team *> _teams;
	bool _good;
	std::string _error;
};

#endif