#include "gtest/gtest.h"
#include "Team.hpp"
#include "Game.hpp"
#include "CSVParser.hpp"
#include <vector>

/**
 * CSV Parser Tests
 */

TEST(CSVParserTests, OpenFile) {
	CSVParser parse("data/test.csv");
	ASSERT_TRUE(parse.good());
}

TEST(CSVParserTests, OpenFileShouldFail) {
	CSVParser parse("data/test1209i09aid0is09da.csv");
	EXPECT_TRUE(parse.fail());
}

TEST(CSVParserTests, SimpleReadRow) {
	CSVParser parse("data/test.csv");
	std::vector<std::string> row = parse.next();
	EXPECT_NE(row.size(), 0);
}

TEST(CSVParserTests, ReadingWholeData) {
	CSVParser parse("data/test.csv");
	std::vector<std::string> row = parse.next();
	EXPECT_STREQ(row[0].c_str(), "id");
	EXPECT_STREQ(row[1].c_str(), "name");
	row = parse.next();
	EXPECT_STREQ(row[0].c_str(), "501");
	EXPECT_STREQ(row[1].c_str(), "Abilene Chr");
	row = parse.next();
	EXPECT_STREQ(row[0].c_str(), "502");
	EXPECT_STREQ(row[1].c_str(), "Air Force");
	row = parse.next();
	EXPECT_STREQ(row[0].c_str(), "503");
	EXPECT_STREQ(row[1].c_str(), "Akron");
	EXPECT_FALSE(parse.good());
}

TEST(CSVParserTests, SkipARow) {
	CSVParser parse("data/test.csv");
	parse.skip();
	std::vector<std::string> row = parse.next();
	EXPECT_STREQ(row[0].c_str(), "501");
	EXPECT_STREQ(row[1].c_str(), "Abilene Chr");
}
