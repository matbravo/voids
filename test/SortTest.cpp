#include <algorithm>
#include "gtest/gtest.h"

using namespace std;

namespace SortTest{
	TEST(SortTest, SortComparison){
		float aux[] = {57.9,54.6,54.2,0.12,394.6,89.1};
		float aux2[] = {0.12,54.2,54.6,57.9,89.1,394.6};
		sort(aux,aux+6);
		for(int k=0; k<6 ; k++){
			ASSERT_EQ(aux[k],aux2[k]);
		}
	}

	bool greaterToLess(int i, int j){ return (i>j); }

	TEST(SortTest, SortGTLComparison){
		float aux[] = {57.9,54.6,54.2,0.12,394.6,89.1};
		float aux2[] = {394.6,89.1,57.9,54.6,54.2,0.12};
		sort(aux,aux+6,greaterToLess);
		for(int k=0; k<6 ; k++){
			ASSERT_EQ(aux[k],aux2[k]);
		}
	}
}