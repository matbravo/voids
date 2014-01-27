#ifndef __ANALYSISCRITERIA2__H
#define __ANALYSISCRITERIA2__H
#include <iostream>
#include <vector>
#include "VoidAnalyzer.hpp"
#include "FacetDictionary.hpp"
#include "PointDictionary.hpp"
#include "Edge.hpp"
using namespace std;

class AnalysisCriteria2 : public VoidAnalyzer{
	protected:
		static bool isBiggerThan(Edge,Edge);
	private:
		void checkNeighbours(Edge edge,FacetDictionary *facetsDict, vector<int> *voidResult, int *facetsInVoid, float *volume, int*);
		float minVolume;
		float minPercentVolume;
		float minEdgeLength;
	public:
		AnalysisCriteria2();
		AnalysisCriteria2(float,float,float);
		~AnalysisCriteria2();
		void analyze(FacetDictionary*);
};


#endif