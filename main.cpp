#include "CSVParser.hpp"
#include <iostream>

using namespace std;

int main(int argc, char const *argv[])
{
	CSVParser parse("data/teams.csv");
	parse.skip();
	while(parse.good()) {
		std::vector<std::string> row = parse.next();
		cout << row[0] << ", " << row[1] << endl;
	}
	return 0;
}