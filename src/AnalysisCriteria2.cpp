#include "AnalysisCriteria2.hpp"
#include <algorithm>
#include <vector>
#include <iostream>
#include <utility>
#include <map>


using namespace std;

AnalysisCriteria2::AnalysisCriteria2():VoidAnalyzer(){}
AnalysisCriteria2::~AnalysisCriteria2(){}

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

	for(vector<Edge>::iterator it = edgeList.begin(); it != edgeList.end() ; ++it){
		Edge edge = *it; // Actual edge
		vector<int> *singleVoid = new vector<int>(); // Facets' id of a single void
		float *volume = new float();
		*volume = 0.0;
		checkNeighbours(edge,facetsDict,singleVoid,volume); // Recursive algorithm to find voids
		if(singleVoid->size() > 0 ){
			// Delete if singleVoid is in border
			int isInBorder = 0;
			for(vector<int>::iterator singleVoid_it = singleVoid->begin(); singleVoid_it != singleVoid->end(); ++singleVoid_it){
				Facet facet = facetsDict->getById(*singleVoid_it);
				if(facet.isInBorder() == 1){
					isInBorder = 1;
					break;
				}
			}
			if( isInBorder == 0 && (*volume) > MIN_VOLUME_CRITERIA_2){ // Add only if not in border
				voidsResult.push_back(*singleVoid);
			}else{
				delete singleVoid;
			}
		}else{
			delete singleVoid;
		}
		delete volume;
	}

	// Look for intersections

	vector< vector < int > > finalVoidsResult;
	finalVoidsResult.push_back(voidsResult.back());
	voidsResult.pop_back();

	while(voidsResult.size() > 0){ // 1 or more voids in set
		vector< int > singleVoidAux = voidsResult.back(); // Take one element from voidsResult
		voidsResult.pop_back();
		vector< vector < int > > finalVoidsResultAux;
		for(vector< vector< int > >::iterator it = finalVoidsResult.begin(); it != finalVoidsResult.end() ; ++it){
			pair< float, vector< int > > intersectionResult = this->intersection(*it,singleVoidAux,facetsDict);
			if(intersectionResult.first > 0){
				singleVoidAux = intersectionResult.second;
			}else{
				finalVoidsResultAux.push_back(*it);
			}
		}
		finalVoidsResultAux.push_back(singleVoidAux);
		finalVoidsResult = finalVoidsResultAux;
	}
 
	result = finalVoidsResult;
}

void AnalysisCriteria2::checkNeighbours(Edge edge,FacetDictionary *facetsDict, vector<int> *voidResult, float* volume){
	EdgeDictionary* edgesDict = facetsDict->getEdgeDictionary();
	vector< int> facetsId = edge.getFacetsId();
	// Get facets who share the same edge
	for(vector<int>::iterator it = facetsId.begin(); it != facetsId.end(); ++it){
		int facetId = *it;
		Facet facet = facetsDict->getById(facetId);
		// Algorithm's conditions for add facets in void result
		if( (facet.getLongestEdge() == edge.getLength()) && // Actual edge is one of the longest edge of the facet
			(facet.getVolume()/(*volume)*100.0 >= MIN_PERCENT_VOLUME_CRITERIA_2)
			){ 
			voidResult->push_back(facetId); // Add facet in result
			(*volume) = (*volume) + facet.getVolume();
			int* edgesId = facet.getEdgesId();
			for(int k = 0; k < 6 ; ++ k){
				checkNeighbours(edgesDict->getById(edgesId[k]),facetsDict,voidResult,volume);
			} 
		}
	}
}

bool AnalysisCriteria2::auxIntersection(int a, int b){
	return (a > b);
}

pair< float , vector < int > > AnalysisCriteria2::intersection(vector<int> void1, vector<int> void2 , FacetDictionary* facetsDict){
	float volume = 0.0;

	sort(void1.begin(),void1.end(),auxIntersection);
	sort(void2.begin(),void2.end(),auxIntersection);

	vector<int> intersectionSet;

	while(void1.size() > 0 && void2.size() > 0 ){
		int a = void1.back();
		int b = void2.back();
		if(a < b){
			intersectionSet.push_back(a);
			void1.pop_back();
		}else if(b < a){
			intersectionSet.push_back(b);
			void2.pop_back();
		}else{
			intersectionSet.push_back(a);
			void1.pop_back();
			void2.pop_back();
			volume+=facetsDict->getById(a).getVolume();
		}
	}

	while(void1.size() > 0){
		intersectionSet.push_back(void1.back());
		void1.pop_back();
	}
	
	while(void2.size() > 0){
		intersectionSet.push_back(void2.back());
		void2.pop_back();
	}

	return make_pair(volume,intersectionSet);
}







