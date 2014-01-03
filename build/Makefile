CC=g++
CFLAGS= -g -Wall

CPP_FILES := $(wildcard ../src/*.cpp)
TEST_CPP_FILES := $(wildcard ../test/*.cpp)
O_FILES = Facet.o FacetTest.o SortTest.o

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

$(O_FILES): $(TEST_CPP_FILES) $(CPP_FILES)
	$(CC) $(CFLAGS) $(INCLUDES) $(LIBS) -c $(TEST_CPP_FILES) $(CPP_FILES) 

clean:
	rm $(TEST) $(MAIN) *.o