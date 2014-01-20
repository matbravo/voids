#ifndef __ANALYSISCRITERIA2__H
#define __ANALYSISCRITERIA2__H
#include <iostream>
#include <vector>
#include "VoidAnalyzer.hpp"
#include "FacetDictionary.hpp"
#include "PointDictionary.hpp"
#include <utility>
#define MIN_VOLUME_CRITERIA_2 7238.0
#define MIN_PERCENT_VOLUME_CRITERIA_2 10
using namespace std;

class AnalysisCriteria2 : public VoidAnalyzer{
	protected:
		static bool isBiggerThan(Edge,Edge);
		static bool auxIntersection(int,int);
	private:
		void checkNeighbours(Edge edge,FacetDictionary *facetsDict, vector<int> *voidResult, float *volume);
		pair< float , vector< int > > intersection(vector<int>,vector<int>,FacetDictionary*);
	public:
		AnalysisCriteria2();
		~AnalysisCriteria2();
		void analyze(FacetDictionary*);
};


#endif