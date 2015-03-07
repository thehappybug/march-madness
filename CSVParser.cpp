/**
 * CSV Parser for C++
 *
 * Adapted from: http://www.zedwood.com/article/cpp-csv-parser
 */

#include "CSVParser.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <istream>

CSVParser::CSVParser(const char *filename) : in(filename)
{
	delimiter = ',';
}

CSVParser::CSVParser(const char *filename, char delim) : in(filename), delimiter(delim)
{
}

bool CSVParser::good()
{
	return in.good();
}

bool CSVParser::fail()
{
	return in.fail();
}

void CSVParser::skip()
{
	char f[256];
	in.getline(f, 256);
}

void CSVParser::skip(int count)
{
	char f[256];
	for (int i = 0; i < count; ++i)
	{
		in.getline(f, 256);
	}
}

std::vector<std::string> CSVParser::next()
{
	std::stringstream ss;
    bool inquotes = false;
    std::vector<std::string> row;
    while(in.good())
    {
        char c = in.get();
        if (!inquotes && c=='"') 
        {
            inquotes=true;
        }
        else if (inquotes && c=='"') 
        {
            if ( in.peek() == '"')
            {
                ss << (char)in.get();
            }
            else 
            {
                inquotes=false;
            }
        }
        else if (!inquotes && c==delimiter) 
        {
            row.push_back( ss.str() );
            ss.str("");
        }
        else if (!inquotes && (c=='\r' || c=='\n') )
        {
            if(in.peek()=='\n') { in.get(); }
            row.push_back( ss.str() );
            return row;
        }
        else
        {
            ss << c;
        }
    }
    std::vector<std::string> a;
    return a;
}

CSVParser::~CSVParser()
{
	if(!in.fail())
		in.close();
}
