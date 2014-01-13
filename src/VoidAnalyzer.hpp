#ifndef __VOIDANALYZER__H
#define __VOIDANALYZER__H
#include <iostream>
#include <vector>
#include "PointDictionary.hpp"
#include "FacetDictionary.hpp"
using namespace std;

class VoidAnalyzer{
	protected:
		vector< vector<int> > result;
	public:
		VoidAnalyzer(){};
		virtual ~VoidAnalyzer(){};
		virtual void analyze(FacetDictionary*) = 0;
		virtual vector< vector< int > > getResult() = 0;
		virtual void printResult(string,FacetDictionary*) = 0;
};



#endif