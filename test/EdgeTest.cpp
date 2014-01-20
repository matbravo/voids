#include "../src/Edge.hpp"
#include "../src/PointDictionary.hpp"
#include "gtest/gtest.h"


namespace EdgeTest{
  class EdgeTest : public ::testing::Test {
  protected:
    EdgeTest() {}
    virtual ~EdgeTest() {}

    virtual void SetUp() {
      edge = new Edge();
      pointsDict = new PointDictionary();
      float point1[3] = {293.14,1923.2,-382.01};
      float point2[3] = {-491.23,-390,62.01};
      //id1 = pointsDict->add(point1);
      //id2 = pointsDict->add(point2);
    }
    virtual void TearDown() {
    // Code here will be called immediately after each test (right
    // before the destructor).
    }
    // Objects declared here can be used by all tests in the test case for Foo.
    Edge *edge;
    PointDictionary* pointsDict;
    int id1,id2;
  };

  // Tests that the Foo::Bar() method does Abc.
  TEST_F(EdgeTest, Id) {
    edge->setId(3);
    ASSERT_EQ(3,edge->getId());
  }
  TEST_F(EdgeTest, pointsId) {
    int aux[2] = {34,56};
    edge->setPointsId(aux);
    int *result = edge->getPointsId();
    ASSERT_EQ(aux[0],result[0]);
    ASSERT_EQ(aux[1],result[1]);
  }
  TEST_F(EdgeTest, facetsId){
    vector<int> aux = {90,41,2,-9,23,56,1,21};
    edge->setFacetsId(aux);
    vector<int> result = edge->getFacetsId();
    for( int it=0; it < 8 ; it++){
      ASSERT_EQ(aux[it],result[it]);
    }
  }
  TEST_F(EdgeTest, length){
    int aux[2] = {id1,id2};
    edge->setPointsId(aux);
  }
}
