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


/**
 * Team and Game tests
 */

 class TeamGameTests : public ::testing::Test {

 protected:
 	Team *Syracuse;
 	Team *North;
 	Team *Maryland;
 	Team *Wake;
 	Game *game;

  	virtual void SetUp() {
  		Syracuse = new Team(0, "Syracuse");
  		North = new Team(1, "North Carolina");
  		Maryland = new Team(2, "Maryland");
  		Wake = new Team(3, "Wake Forest"); 

		game = new Game(Syracuse, North, 78, 72, 'N');
  		Game *game0 = new Game(Syracuse, Maryland, 82, 68, 'N');
  		game0->winner();
  		game0 = new Game(Syracuse, Wake, 72, 71, 'N');
  		game0 = new Game(North, Syracuse, 93, 68, 'N');
  		game0 = new Game(Maryland, Wake, 81, 72, 'N');
  		game0 = new Game(North, Wake, 68, 52, 'N');
  	}

};

TEST_F(TeamGameTests, CreatingTeams) {
	EXPECT_EQ(Syracuse->id(), 0);
	EXPECT_STREQ(Syracuse->name().c_str(), "Syracuse");
	EXPECT_EQ(North->id(), 1);
	EXPECT_STREQ(North->name().c_str(), "North Carolina");
	EXPECT_EQ(Maryland->id(), 2);
	EXPECT_STREQ(Maryland->name().c_str(), "Maryland");
	EXPECT_EQ(Wake->id(), 3);
	EXPECT_STREQ(Wake->name().c_str(), "Wake Forest");
}

TEST_F(TeamGameTests, CalculatingWinningPercentage) {
	EXPECT_FLOAT_EQ(Syracuse->winningPercentage(), 0.75);
	EXPECT_FLOAT_EQ(North->winningPercentage(), 2.0/3.0);
	EXPECT_FLOAT_EQ(Maryland->winningPercentage(), 0.5);
	EXPECT_FLOAT_EQ(Wake->winningPercentage(), 0.0);
}

TEST_F(TeamGameTests, CalculatingWinningPercentageExclude) {
	EXPECT_FLOAT_EQ(North->winningPercentageExcluding(Syracuse), 1.0);
	EXPECT_FLOAT_EQ(Maryland->winningPercentageExcluding(Syracuse), 1.0);
	EXPECT_FLOAT_EQ(Wake->winningPercentageExcluding(Syracuse), 0.0);
}

TEST_F(TeamGameTests, CalculatingOpponentsWinningPercentage) {
	EXPECT_NEAR(Syracuse->opponentsWinningPercentage(), 0.75, 0.0001);
	EXPECT_NEAR(North->opponentsWinningPercentage(), 0.666667, 0.0001);
	EXPECT_NEAR(Maryland->opponentsWinningPercentage(), 0.333333, 0.0001);
	EXPECT_NEAR(Wake->opponentsWinningPercentage(), 0.388889, 0.0001);
}

TEST_F(TeamGameTests, CalculatingOpponentsOpponentsWinningPercentage) {
	EXPECT_NEAR(Syracuse->opponentsOpponentsWinningPercentage(), 0.513889, 0.0001);
	EXPECT_NEAR(North->opponentsOpponentsWinningPercentage(), 0.62963, 0.0001);
	EXPECT_NEAR(Maryland->opponentsOpponentsWinningPercentage(), 0.569444, 0.0001);
	EXPECT_NEAR(Wake->opponentsOpponentsWinningPercentage(), 0.583333, 0.0001);
}

TEST_F(TeamGameTests, CalculatingRPI) {
	EXPECT_NEAR(Syracuse->ratingsPercentageIndex(), 0.690972, 0.0001);
	EXPECT_NEAR(North->ratingsPercentageIndex(), 0.657407, 0.0001);
	EXPECT_NEAR(Maryland->ratingsPercentageIndex(), 0.434028, 0.0001);
	EXPECT_NEAR(Wake->ratingsPercentageIndex(), 0.340278, 0.0001);
}

