#include "AnalysisCriteria1.hpp"
#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;

AnalysisCriteria1::AnalysisCriteria1():VoidAnalyzer(){}
AnalysisCriteria1::~AnalysisCriteria1(){}

vector < vector < Facet* > > AnalysisCriteria1::getResult(){
	return this->result;
}
bool isBiggerThan(Edge* a, Edge* b){ 
	return (a->getLength() > b->getLength());
}
void AnalysisCriteria1::analyze(FacetDictionary *facetsDict){
	vector < vector < Facet* > > voidsResult;
	EdgeDictionary* edgesDict = facetsDict->getEdgeDictionary();
	vector<Edge*> edgeList;
	for(int k=0 ; k < edgesDict->getDataLength() ; k++){
		edgeList.push_back(edgesDict->getById(k));
	}
	sort(edgeList.begin(),edgeList.end(),isBiggerThan); // Complexity N log N
	int facetsVisited[facetsDict->getDataLength()]; // Array contains facets marked by algorithm
	


}

