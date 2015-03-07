#ifndef CSVParser_H_
#define CSVParser_H_

#include <vector>
#include <fstream>

class CSVParser
{
private:
	std::ifstream in;
	char delimiter;
	bool fileStillOpen;
public:
	CSVParser(const char *filename);
	CSVParser(const char *filename, char delimiter);
	void skip();
	void skip(int count);
	bool good();
	bool fail();
	std::vector<std::string> next();
	~CSVParser();
};

#endif