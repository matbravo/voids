#include "gtest/gtest.h"
#include "../src/PointDictionary.hpp"
#include <iostream>
#include <fstream>
#include <stdio.h>

namespace DictionaryTest{
  class DictionaryTest : public ::testing::Test {
  protected:
    DictionaryTest() {}
    virtual ~DictionaryTest() {}

    virtual void SetUp() {
      // Set up variables for test
      dictPoints = new PointDictionary();
    }
    virtual void TearDown() {
    // Code here will be called immediately after each test (right
    // before the destructor).
    }
    // Objects declared here can be used by all tests in the test case for Foo.
    PointDictionary* dictPoints;
  };

  // Tests that the Foo::Bar() method does Abc.
  TEST_F(DictionaryTest, load){
  	string output_file = "dictPointsTestFile";
  	ofstream ofs(output_file.c_str());
  	if(ofs.good()){
	  	ofs << "3\n";
	  	ofs << "2\n";
	  	ofs << "456.3431\t7819.43523452\t9991.20\n";
	  	ofs << "1232134.432\t43124231.432\t-12314.23\n";
	  	ofs.close();
	  	
	  	dictPoints->load(output_file);
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

}