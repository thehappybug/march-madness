#include "CSVParser.hpp"
#include "Team.hpp"
#include "Game.hpp"
#include <iostream>
#include <assert.h>

using namespace std;

// int main(int argc, char const *argv[])
// {
// 	CSVParser parse("data/teams.csv");
// 	parse.skip();
// 	while(parse.good()) {
// 		std::vector<std::string> row = parse.next();
// 		cout << row[0] << ", " << row[1] << endl;
// 	}
// 	return 0;
// }

/**
Home			Score	Away			Score
Syracuse		78		North Carolina	72
Syracuse		82		Maryland		68
Wake Forest		71		Syracuse		72
North Carolina	93		Syracuse		68
Maryland		81		Wake Forest		72
Wake Forest		52		North Carolina	68

 */

int main(int argc, char const *argv[])
{
	Team *Syracuse = new Team(0, "Syracuse");
	Team *North = new Team(1, "North Carolina");
	Team *Maryland = new Team(2, "Maryland");
	Team *Wake = new Team(3, "Wake Forest");

	Game *game = new Game(Syracuse, North, 78, 72);
	assert(game->winner() == Syracuse);
	assert(game->loser() == North);
	assert(game->winner()->gamesWon()[0] == game);
	assert(game->loser()->gamesPlayed()[0] == game);

	game = new Game(Syracuse, Maryland, 82, 68);
	game = new Game(Syracuse, Wake, 72, 71);
	game = new Game(North, Syracuse, 93, 68);
	game = new Game(Maryland, Wake, 81, 72);
	game = new Game(North, Wake, 68, 52);

	cout << Syracuse->winningPercentage() << endl;
	cout << North->winningPercentage() << endl;
	cout << Maryland->winningPercentage() << endl;
	cout << Wake->winningPercentage() << endl;

	cout << "OWP" << endl;
	// cout << North->winningPercentageExcluding(Syracuse) << endl;
	// cout << North->winningPercentageExcluding(Syracuse) << endl;
	// cout << Maryland->winningPercentageExcluding(Syracuse) << endl;
	// cout << Wake->winningPercentageExcluding(Syracuse) << endl;
	cout << Syracuse->opponentsWinningPercentage() << endl;
	cout << North->opponentsWinningPercentage() << endl;
	cout << Maryland->opponentsWinningPercentage() << endl;
	cout << Wake->opponentsWinningPercentage() << endl;

	cout << "OOWP" << endl;
	cout << Syracuse->opponentsOpponentsWinningPercentage() << endl;
	cout << North->opponentsOpponentsWinningPercentage() << endl;
	cout << Maryland->opponentsOpponentsWinningPercentage() << endl;
	cout << Wake->opponentsOpponentsWinningPercentage() << endl;

	cout << "RPI" << endl;
	cout << Syracuse->ratingsPercentageIndex() << endl;
	cout << North->ratingsPercentageIndex() << endl;
	cout << Maryland->ratingsPercentageIndex() << endl;
	cout << Wake->ratingsPercentageIndex() << endl;

	return 0;
}