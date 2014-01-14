#ifndef __ANALYSISCRITERIA1__H
#define __ANALYSISCRITERIA1__H
#include <iostream>
#include <vector>
#include "VoidAnalyzer.hpp"
#include "FacetDictionary.hpp"
#include "PointDictionary.hpp"
#define MIN_VOLUME 7238.0

using namespace std;
class AnalysisCriteria1 : public VoidAnalyzer{
	private:
		void checkNeighbours(Edge* edge,FacetDictionary *facetsDict, vector<int> *voidResult, int *facetsInVoid);
	public:
		AnalysisCriteria1();
		~AnalysisCriteria1();
		void analyze(FacetDictionary*);
		vector < vector< int > > getResult();
		void printResult(string,FacetDictionary*);
};


#endif