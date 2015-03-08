# A sample Makefile for building Google Test and using it in user
# tests.  Please tweak it to suit your environment and project.  You
# may want to move it to your project's root directory.
#
# SYNOPSIS:
#
#   make [all]  - makes everything.
#   make TARGET - makes the given target.
#   make clean  - removes all files generated by make.

# Please tweak the following variable definitions as needed by your
# project, except GTEST_HEADERS, which you can use in your own targets
# but shouldn't modify.

# Points to the root of Google Test, relative to where this file is.
# Remember to tweak this if you move this file.
# GTEST_DIR = ..

# Where to find user code.
USER_DIR = ./

# Flags passed to the preprocessor.
# Set Google Test's header directory as a system directory, such that
# the compiler doesn't generate warnings in Google Test headers.
CPPFLAGS += -std=gnu++11 -isystem $(GTEST_DIR)/include

# Flags passed to the C++ compiler.
CXXFLAGS += -g -Wall -Wextra -pthread

# All tests produced by this Makefile.  Remember to add new tests you
# created to the list.
TESTS = unittest

# All Google Test headers.  Usually you shouldn't change this
# definition.
GTEST_HEADERS = $(GTEST_DIR)/include/gtest/*.h \
                $(GTEST_DIR)/include/gtest/internal/*.h

# House-keeping build targets.

all : $(TESTS) main

clean :
	rm -f $(TESTS) gtest.a gtest_main.a *.o

# Builds gtest.a and gtest_main.a.

# Usually you shouldn't tweak such internal variables, indicated by a
# trailing _.
GTEST_SRCS_ = $(GTEST_DIR)/src/*.cc $(GTEST_DIR)/src/*.h $(GTEST_HEADERS)

# For simplicity and to avoid depending on Google Test's
# implementation details, the dependencies specified below are
# conservative and not optimized.  This is fine as Google Test
# compiles fast and for ordinary users its source rarely changes.
gtest-all.o : $(GTEST_SRCS_)
	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c \
            $(GTEST_DIR)/src/gtest-all.cc

gtest_main.o : $(GTEST_SRCS_)
	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c \
            $(GTEST_DIR)/src/gtest_main.cc

gtest.a : gtest-all.o
	$(AR) $(ARFLAGS) $@ $^

gtest_main.a : gtest-all.o gtest_main.o
	$(AR) $(ARFLAGS) $@ $^

# Builds a sample test.  A test should link with either gtest.a or
# gtest_main.a, depending on whether it defines its own main()
# function.

Team.o : $(USER_DIR)/Team.cpp $(USER_DIR)/Team.hpp $(USER_DIR)/Game.hpp $(GTEST_HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $(USER_DIR)/Team.cpp

Game.o : $(USER_DIR)/Game.cpp $(USER_DIR)/Game.hpp $(USER_DIR)/Team.hpp $(GTEST_HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $(USER_DIR)/Game.cpp

CSVParser.o : $(USER_DIR)/CSVParser.cpp $(USER_DIR)/CSVParser.hpp $(GTEST_HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $(USER_DIR)/CSVParser.cpp

GameDataAdapter.o : $(USER_DIR)/GameDataAdapter.cpp $(USER_DIR)/GameDataAdapter.hpp $(USER_DIR)/Game.hpp $(USER_DIR)/Team.hpp $(USER_DIR)/CSVParser.hpp $(GTEST_HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $(USER_DIR)/GameDataAdapter.cpp

QueryFactory.o : $(USER_DIR)/QueryFactory.cpp $(USER_DIR)/QueryFactory.hpp $(USER_DIR)/QueryBase.hpp $(GTEST_HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $(USER_DIR)/QueryFactory.cpp

RPIChampionQuery.o : $(USER_DIR)/RPIChampionQuery.cpp $(USER_DIR)/RPIChampionQuery.hpp $(USER_DIR)/QueryBase.hpp $(USER_DIR)/QueryFactory.hpp  $(USER_DIR)/Game.hpp $(USER_DIR)/Team.hpp $(GTEST_HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $(USER_DIR)/RPIChampionQuery.cpp

ListGamesQuery.o : $(USER_DIR)/ListGamesQuery.cpp $(USER_DIR)/ListGamesQuery.hpp $(USER_DIR)/QueryBase.hpp $(USER_DIR)/QueryFactory.hpp  $(USER_DIR)/Game.hpp $(USER_DIR)/Team.hpp $(GTEST_HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $(USER_DIR)/ListGamesQuery.cpp

main.o : $(USER_DIR)/main.cpp $(GTEST_HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $(USER_DIR)/main.cpp

unittest.o : $(USER_DIR)/unittest.cpp $(GTEST_HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $(USER_DIR)/unittest.cpp

unittest : unittest.o Team.o Game.o CSVParser.o gtest_main.a
ifndef GTEST_DIR
	$(info Enviroment variable GTEST_DIR needs to be set before compilation.)
	exit 1
endif
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -lpthread $^ -o $@

main: Team.o Game.o CSVParser.o GameDataAdapter.o main.o QueryFactory.o RPIChampionQuery.o ListGamesQuery.o
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -o madness main.o Team.o Game.o CSVParser.o GameDataAdapter.o QueryFactory.o RPIChampionQuery.o ListGamesQuery.o
