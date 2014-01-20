#ifndef __ANALYSISCRITERIA1__H
#define __ANALYSISCRITERIA1__H
#include <iostream>
#include <vector>
#include "VoidAnalyzer.hpp"
#include "FacetDictionary.hpp"
#include "PointDictionary.hpp"
#include "Edge.hpp"
#define MIN_VOLUME_CRITERIA_1 7238.0
#define MIN_PERCENT_VOLUME_CRITERIA_1 10
using namespace std;

class AnalysisCriteria1 : public VoidAnalyzer{
	protected:
		static bool isBiggerThan(Edge,Edge);
	private:
		vector< vector <int> > voidsDeleted;
		void checkNeighbours(Edge edge,FacetDictionary *facetsDict, vector<int> *voidResult, int *facetsInVoid, float *volume);
	public:
		AnalysisCriteria1();
		~AnalysisCriteria1();
		void analyze(FacetDictionary*);
		//void printResultOFF(string,FacetDictionary*);
};


#endif