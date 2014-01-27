#ifndef __ANALYSISCRITERIA1__H
#define __ANALYSISCRITERIA1__H
#include <iostream>
#include <vector>
#include "VoidAnalyzer.hpp"
#include "FacetDictionary.hpp"
#include "PointDictionary.hpp"
#include "Edge.hpp"
using namespace std;

class AnalysisCriteria1 : public VoidAnalyzer{
	protected:
		static bool isBiggerThan(Edge,Edge);
	private:
		void checkNeighbours(Edge edge,FacetDictionary *facetsDict, vector<int> *voidResult, int *facetsInVoid, float *volume, int*);
		float minVolume;
		float minPercentVolume;
	public:
		AnalysisCriteria1();
		AnalysisCriteria1(float,float);
		~AnalysisCriteria1();
		void analyze(FacetDictionary*);
};


#endif