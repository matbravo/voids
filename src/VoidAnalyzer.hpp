#ifndef __VOIDANALYZER__H
#define __VOIDANALYZER__H
#include <iostream>
#include <vector>
#include "PointDictionary.hpp"
#include "FacetDictionary.hpp"
#define PI 3.1415926
using namespace std;

class VoidAnalyzer{
	protected:
		vector< vector<int> > result;
	public:
		VoidAnalyzer(){};
		virtual ~VoidAnalyzer(){};
		virtual void analyze(FacetDictionary*) = 0;
		vector< vector< int > > getResult();
		void printResult(string,FacetDictionary*);
		virtual void printResultOFF(string,FacetDictionary*);
};



#endif