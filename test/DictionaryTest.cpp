#include "gtest/gtest.h"
#include "../src/PointDictionary.hpp"
#include "../src/FacetDictionary.hpp"
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <math.h>

namespace DictionaryTest{
  class DictionaryTest : public ::testing::Test {
  protected:
    DictionaryTest() {}
    virtual ~DictionaryTest() {}

    virtual void SetUp() {
      // Set up variables for test
      dictPoints = new PointDictionary();
      dictFacets = new FacetDictionary();
    }
    virtual void TearDown() {
    // Code here will be called immediately after each test (right
    // before the destructor).
    }
    // Objects declared here can be used by all tests in the test case for Foo.
    PointDictionary* dictPoints;
    FacetDictionary* dictFacets;
  };

  // Tests that the Foo::Bar() method does Abc.
  TEST_F(DictionaryTest, PointsLoad){
  	string output_file = "dictPointsTestFile.dat";
  	ofstream ofs(output_file.c_str());
  	if(ofs.good()){
	  	ofs << "3\n";
	  	ofs << "2\n";
	  	ofs << "456.3431\t7819.43523452\t9991.20\n";
	  	ofs << "1232134.432\t43124231.432\t-12314.23\n";
	  	ofs.close();
	  	
	  	dictPoints->load("dictPointsTestFile");
	  	float* firstPoint = dictPoints->getById(0);
	  	float* secondPoint = dictPoints->getById(1);

	  	remove(output_file.c_str());
	  	
	  	ASSERT_EQ(firstPoint[0],float(456.3431));
	  	ASSERT_EQ(firstPoint[1],float(7819.43523452));
	  	ASSERT_EQ(firstPoint[2],float(9991.20));

	  	ASSERT_EQ(secondPoint[0],float(1232134.432));
	  	ASSERT_EQ(secondPoint[1],float(43124231.432));
	  	ASSERT_EQ(secondPoint[2],float(-12314.23));
  	}
  	
  }
  TEST_F(DictionaryTest, FacetLoad){
    string output_file_neighbours = "dictFacetsTestFile_neighbours.dat";
    string output_file_vertexes = "dictFacetsTestFile_vertex.dat";

    ofstream neighbours_ofs(output_file_neighbours.c_str());
    ofstream vertexes_ofs(output_file_vertexes.c_str());

    if(neighbours_ofs.good()){
      neighbours_ofs << "4\n";
      neighbours_ofs << "4 1234 4331 4314 55\n";
      neighbours_ofs << "4 83 7583 38 21\n";
      neighbours_ofs << "4 321 32 1 23\n";
      neighbours_ofs << "4 123 13 22 34\n";
      neighbours_ofs.close(); 
    }

    if(vertexes_ofs.good()){
      vertexes_ofs << "4\n";
      vertexes_ofs << "4 91 89 72 2\n";
      vertexes_ofs << "4 33 123 43 1\n";
      vertexes_ofs << "4 18 22 12 43\n";
      vertexes_ofs << "4 2 32 31 89\n";
      vertexes_ofs.close();
    }

    dictFacets->load("dictFacetsTestFile");

    remove("dictFacetsTestFile_vertex.dat");
    remove("dictFacetsTestFile_neighbours.dat");

    Facet* firstFacet = dictFacets->getById(0);
    Facet* secondFacet = dictFacets->getById(1);
    //Facet* thirdFacet = dictFacets-> getById(2);
    //Facet* fourthFacet = dictFacets->getById(3);

    // Test firstFacet
    ASSERT_EQ(firstFacet->getNeighboursId()[0],1234);
    ASSERT_EQ(firstFacet->getNeighboursId()[1],4331);
    ASSERT_EQ(firstFacet->getNeighboursId()[2],4314);
    ASSERT_EQ(firstFacet->getNeighboursId()[3],55);

    ASSERT_EQ(firstFacet->getPointsId()[0],91);
    ASSERT_EQ(firstFacet->getPointsId()[1],89);
    ASSERT_EQ(firstFacet->getPointsId()[2],72);
    ASSERT_EQ(firstFacet->getPointsId()[3],2);

    // Test secondFacet
    ASSERT_EQ(secondFacet->getNeighboursId()[0],83);
    ASSERT_EQ(secondFacet->getNeighboursId()[1],7583);
    ASSERT_EQ(secondFacet->getNeighboursId()[2],38);
    ASSERT_EQ(secondFacet->getNeighboursId()[3],21);

    ASSERT_EQ(secondFacet->getPointsId()[0],33);
    ASSERT_EQ(secondFacet->getPointsId()[1],123);
    ASSERT_EQ(secondFacet->getPointsId()[2],43);
    ASSERT_EQ(secondFacet->getPointsId()[3],1);

  }

  TEST_F(DictionaryTest,RefreshDataTest){
    string output_file = "dictPointsTestFile.dat";
    ofstream ofs(output_file.c_str());
    if(ofs.good()){
        ofs << "3\n";
        ofs << "4\n";
        ofs << "0\t0\t-1\n";
        ofs << "0\t0\t11\n";
        ofs << "5\t0\t-1\n";
        ofs << "0\t5\t-1\n";
        ofs.close();
        
        dictPoints->load("dictPointsTestFile");

        remove(output_file.c_str());
    }

    string output_file_neighbours = "dictFacetsTestFile_neighbours.dat";
    string output_file_vertexes = "dictFacetsTestFile_vertex.dat";

    ofstream neighbours_ofs(output_file_neighbours.c_str());
    ofstream vertexes_ofs(output_file_vertexes.c_str());

    if(neighbours_ofs.good()){
      neighbours_ofs << "1\n";
      neighbours_ofs << "4 1 4331 4314 55\n";
      neighbours_ofs.close(); 
    }

    if(vertexes_ofs.good()){
      vertexes_ofs << "1\n";
      vertexes_ofs << "4 1 3 2 0\n";
      vertexes_ofs.close();
    }

    dictFacets->load("dictFacetsTestFile");
    remove("dictFacetsTestFile_vertex.dat");
    remove("dictFacetsTestFile_neighbours.dat");

    dictFacets->setPointDictionary(dictPoints);

    Facet* aux= dictFacets->getById(0);
    ASSERT_EQ(aux->getLongestEdge(),sqrt(pow(12,2)+pow(5,2)));
  }

}