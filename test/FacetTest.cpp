#include "../src/Facet.hpp"
#include "gtest/gtest.h"


namespace FacetTest{
  class FacetTest : public ::testing::Test {
  protected:
    FacetTest() {}
    virtual ~FacetTest() {}

    virtual void SetUp() {
      // Set up variables for test
      int points[4] = {34,56,12,78};
      int neighbours[4] = {0,41,2,-9};
      facet = new Facet(1,points,neighbours);
    }
    virtual void TearDown() {
    // Code here will be called immediately after each test (right
    // before the destructor).
    }
    // Objects declared here can be used by all tests in the test case for Foo.
    Facet *facet;
  };

  // Tests that the Foo::Bar() method does Abc.
  TEST_F(FacetTest, getId) {
    ASSERT_EQ(1,facet->getId());
  }
  TEST_F(FacetTest, setId){
    facet->setId(4);
    ASSERT_EQ(4,facet->getId());
  }
  TEST_F(FacetTest, getPointsId) {
    int aux[4] = {34,56,12,78};
    int *result= facet->getPointsId();
    for( int it=0; it < 4 ; it++){
      ASSERT_EQ(aux[it],result[it]);
    }
  }
  TEST_F(FacetTest, setPointsId) {
    int aux[4] = {58,90,102,3};
    facet->setPointsId(aux);
    int *result= facet->getPointsId();
    for( int it=0; it < 4 ; it++){
      ASSERT_EQ(aux[it],result[it]);
    }
  }
  TEST_F(FacetTest, getNeighboursId){
    int aux[4] = {0,41,2,-9};
    int *result= facet->getNeighboursId();
    for( int it=0; it < 4 ; it++){
      ASSERT_EQ(aux[it],result[it]);
    }
  }
  TEST_F(FacetTest, setNeighboursId){
    int aux[4] = {-4,51,72,-10};
    facet->setNeighboursId(aux);
    int *result= facet->getNeighboursId();
    for( int it=0; it < 4 ; it++){
      ASSERT_EQ(aux[it],result[it]);
    }
  }

}
