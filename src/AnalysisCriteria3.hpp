#ifndef __ANALYSISCRITERIA3__H
#define __ANALYSISCRITERIA3__H
#include <iostream>
#include <vector>
#include "VoidAnalyzer.hpp"
#include "FacetDictionary.hpp"
#include "PointDictionary.hpp"
#include "Edge.hpp"
#include "VoidContainer.hpp"
#include <utility>
using namespace std;

class AnalysisCriteria3 : public VoidAnalyzer{
	protected:
		static bool isBiggerThan(Edge,Edge);
	private:
		void checkNeighbours(Edge,FacetDictionary*,vector<int>*,float*,int);
		int joinVoids(int,int,VoidContainer*);
		float faceArea(float*,float*,float*);
		float minVolume;
		float minPercentVolume;
		float minEdgeLength;
	public:
		AnalysisCriteria3();
		AnalysisCriteria3(float,float,float);
		~AnalysisCriteria3();
		void analyze(FacetDictionary*);
};


#endif