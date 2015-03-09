#ifndef CSVParser_H_
#define CSVParser_H_

#include <vector>
#include <fstream>

/**
 * A general purpose CSV file parser
 */
class CSVParser
{
public:
	// Open filename for parsing; delimiter=','
	CSVParser(const char *filename);

	// Open filename for parsing; use specified delimier
	CSVParser(const char *filename, char delimiter);

	// Skip 1 record
	void skip();

	// Skip 'n' record
	void skip(int count);

	// Is more data available?
	bool good();

	// Is parser stable? Always check after opening a file
	bool fail();

	// Read and return a row broken in string vector
	std::vector<std::string> next();
	
	~CSVParser();
private:
	std::ifstream in;
	char delimiter;
	bool fileStillOpen;
};

#endif