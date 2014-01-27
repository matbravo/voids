#include "AnalysisCriteria2.hpp"
#include <algorithm>
#include <vector>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include <iomanip>
#include <math.h>


using namespace std;

AnalysisCriteria2::~AnalysisCriteria2(){}
AnalysisCriteria2::AnalysisCriteria2():VoidAnalyzer(){
	minVolume = 0.0;
	minPercentVolume = 0.0;
	minEdgeLength = 0.0;
}
AnalysisCriteria2::AnalysisCriteria2(float _minVolume, float _minPercentVolume, float _minEdgeLength){
	minVolume = _minVolume;
	minPercentVolume = _minPercentVolume;
	minEdgeLength = _minEdgeLength;
}
bool AnalysisCriteria2::isBiggerThan(Edge a, Edge b){ 
	return (a.getLength() > b.getLength());
}

void AnalysisCriteria2::analyze(FacetDictionary *facetsDict){
	cout << "Analyzing ...\n";
	vector < vector < int > > voidsResult; // Facets id in voids
	EdgeDictionary* edgesDict = facetsDict->getEdgeDictionary();

	vector<Edge> edgeList(edgesDict->getDataLength()); // Edge list used by sort
	for(int k=0 ; k < edgesDict->getDataLength() ; k++){
		edgeList[k] = edgesDict->getById(k);
	}
	sort(edgeList.begin(),edgeList.end(),&AnalysisCriteria2::isBiggerThan); // Complexity N log N


	int *facetsInVoid= new int[facetsDict->getDataLength()]; // Array contains facets marked visited by analysis
	for(int i=0;i < facetsDict->getDataLength();++i){
			facetsInVoid[i] = 0;
		}
	float *volume = new float();
	int *isInBorder = new int();
	for(vector<Edge>::iterator it = edgeList.begin(); it != edgeList.end() ; ++it){
		Edge edge = *it; // Actual edge
		if(edge.getLength() < minEdgeLength) break;
		vector<int> *singleVoid = new vector<int>(); // Facets' id of a single void
		*volume = 0.0;
		*isInBorder = 0;
		checkNeighbours(edge,facetsDict,singleVoid,facetsInVoid,volume,isInBorder); // Recursive algorithm to find voids
		if(singleVoid->size() > 0 ){
			// Delete if singleVoid is in border
			if( *isInBorder == 0 && (*volume) > minVolume){ // Add only if not in border
				voidsResult.push_back(*singleVoid);
			}else{
				for(vector<int>::iterator singleVoid_it = singleVoid->begin(); singleVoid_it != singleVoid->end(); ++singleVoid_it){
					facetsInVoid[*singleVoid_it] = 0;
				}
				delete singleVoid;
			}
		}else{
			delete singleVoid;
		}
	}
	delete volume;
	delete isInBorder;
	delete [] facetsInVoid;
	result = voidsResult;
}

void AnalysisCriteria2::checkNeighbours(Edge edge,FacetDictionary *facetsDict, vector<int> *voidResult, int *facetsInVoid, float* volume, int* isInBorder){
	if(edge.getLength() < minEdgeLength) return;
	EdgeDictionary* edgesDict = facetsDict->getEdgeDictionary();
	vector< int> facetsId = edge.getFacetsId();
	// Get facets who share the same edge
	for(vector<int>::iterator it = facetsId.begin(); it != facetsId.end(); ++it){
		int facetId = *it;
		Facet facet = facetsDict->getById(facetId);
		// Algorithm's conditions for add facets in void result
		if( (facetsInVoid[facetId] == 0) &&  // Facet not in a void
			(facet.getLongestEdge() == edge.getLength()) && // Actual edge is one of the longest edge of the facet
			(facet.getVolume()/(*volume)*100.0 >= minPercentVolume)
			){ 
			facetsInVoid[facetId] = 1; // Set facet in void
			voidResult->push_back(facetId); // Add facet in result
			(*volume) = (*volume) + facet.getVolume();
			if(facet.isInBorder() == 1){
				*isInBorder = 1;
			}
			int* edgesId = facet.getEdgesId();
			for(int k = 0; k < 6 ; ++ k){
				if(edgesId[k] != edge.getId()){
					checkNeighbours(edgesDict->getById(edgesId[k]),facetsDict,voidResult,facetsInVoid,volume,isInBorder);
				}
			} 
		}
	}
}








