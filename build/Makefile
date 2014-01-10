CC=g++
CFLAGS= -g -Wall -std=c++11

CPP_FILES := $(wildcard ../src/*.cpp)
TEST_CPP_FILES := $(wildcard ../test/*.cpp)
HPP_FILES := $(wildcard ../src/*.hpp)
O_FILES = Facet.o Edge.o FacetTest.o SortTest.o DictionaryTest.o PointDictionary.o FacetDictionary.o EdgeDictionary.o AnalysisCriteria1.o

BUILD= build
TEST= test
MAIN = main

INCLUDES= -I../include
LFLAGS = -L../lib
LIBS = -lgtest -lgtest_main -lpthread


main: $(O_FILES) main.o 
	$(CC) $(CFLAGS) $(INCLUDES) $(LIBS) $(O_FILES) main.o -o $(MAIN)

testfile: $(O_FILES) testmain.o
	$(CC) $(CFLAGS) $(INCLUDES) $(LIBS) $(O_FILES) testmain.o -o $(TEST) && ./test

$(O_FILES): $(TEST_CPP_FILES) $(CPP_FILES) $(HPP_FILES)
	$(CC) $(CFLAGS) $(INCLUDES) $(LIBS) -c $(TEST_CPP_FILES) $(CPP_FILES)

clean:
	rm $(TEST) $(MAIN) *.o dictPointsTestFile