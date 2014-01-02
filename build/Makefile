CC=g++
CFLAGS= -g -Wall

CPP_FILES := $(wildcard ../src/*.cpp)
TEST_CPP_FILES := $(wildcard ../test/*.cpp)
O_FILES = Facet.o FacetTest.o main.o SortTest.o

BUILD= build
TEST= test

INCLUDES= -I../include
LFLAGS = -L../lib
LIBS = -lgtest -lgtest_main -lpthread


testfile: $(O_FILES)
	$(CC) $(CFLAGS) $(INCLUDES) $(LIBS) $(O_FILES) -o $(TEST) && ./test

$(O_FILES): $(TEST_CPP_FILES) $(CPP_FILES)
	$(CC) $(CFLAGS) $(INCLUDES) $(LIBS) -c $(TEST_CPP_FILES) $(CPP_FILES) 

clean:
	rm $(TEST) *.o