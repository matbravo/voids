#ifndef __VOIDANALYZER__H
#define __VOIDANALYZER__H
#include <iostream>
#include <vector>
#include "PointDictionary.hpp"
#include "FacetDictionary.hpp"
using namespace std;

class VoidAnalyzer{
	protected:
		vector< vector<Facet*> > result;
	public:
		VoidAnalyzer(){};
		virtual ~VoidAnalyzer(){};
		virtual void analyze(FacetDictionary*) = 0;
		virtual vector< vector< Facet* > > getResult() = 0;
};



#endif