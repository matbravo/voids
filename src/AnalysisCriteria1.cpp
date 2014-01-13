#include "AnalysisCriteria1.hpp"
#include <algorithm>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

AnalysisCriteria1::AnalysisCriteria1():VoidAnalyzer(){}
AnalysisCriteria1::~AnalysisCriteria1(){}

vector < vector < int > > AnalysisCriteria1::getResult(){
	return this->result;
}
bool isBiggerThan(Edge* a, Edge* b){ 
	return (a->getLength() > b->getLength());
}

void AnalysisCriteria1::analyze(FacetDictionary *facetsDict){
	vector < vector < int > > voidsResult; // Facets id in voids
	EdgeDictionary* edgesDict = facetsDict->getEdgeDictionary();
	vector<Edge*> edgeList(edgesDict->getDataLength());
	for(int k=0 ; k < edgesDict->getDataLength() ; k++){
		edgeList[k] = edgesDict->getById(k);
	}
	sort(edgeList.begin(),edgeList.end(),isBiggerThan); // Complexity N log N
	int *facetsInVoid= new int[facetsDict->getDataLength()]; // Array contains facets marked visited by analyze

	for(vector<Edge*>::iterator it = edgeList.begin(); it != edgeList.end() ; ++it){
		Edge* edge = *it;
		vector<int> *singleVoid = new vector<int>(); // Facets' id of a single void
		checkNeighbours(edge,facetsDict,singleVoid,facetsInVoid);
		if(singleVoid->size() > 0 ){
			// Delete if 
			voidsResult.push_back(*singleVoid);
		}else{
			delete(singleVoid);
		}
	}
	result = voidsResult;
}

void AnalysisCriteria1::checkNeighbours(Edge* edge,FacetDictionary *facetsDict, vector<int> *voidResult, int *facetsInVoid){
	EdgeDictionary* edgesDict = facetsDict->getEdgeDictionary();
	vector< int> facetsId = edge->getFacetsId();
	// Get facets who share the same edge
	for(vector<int>::iterator it = facetsId.begin(); it != facetsId.end(); ++it){
		int facetId = *it;
		Facet* facet = facetsDict->getById(facetId);
		// Algorithm's conditions for add facets in void result
		if( (facetsInVoid[facetId] == 0) &&  // Facet not in a void
			(facet->getLongestEdge() == edge->getLength()) // Actual edge is one of the longest edge of the facet
			){ 
			facetsInVoid[facetId] = 1; // Set facet in void
			voidResult->push_back(facetId); // Add facet in result
			int* edgesId = facet->getEdgesId();
			for(int k = 0; k < 6 ; ++ k){
				checkNeighbours(edgesDict->getById(edgesId[k]),facetsDict,voidResult,facetsInVoid);
			} 
		}
	}
}

void AnalysisCriteria1::printResult(string filename, FacetDictionary* facetsDict){
	string outputFile = filename+string("_output.dat");
	ofstream ofs(outputFile.c_str());
	if(ofs.good()){
		int void_k =0;
		for(vector< vector< int > >::iterator it = this->result.begin() ; it != this->result.end() ; ++it){
			float centroid[3];
			centroid[0] = 0.0;
			centroid[1] = 0.0;
			centroid[2] = 0.0;
			float volume = 0.0;
			for(vector<int>::iterator void_it = (*it).begin(); void_it != (*it).end() ; ++void_it){
				Facet* facet = facetsDict->getById(*void_it);
				volume = volume + facet->getVolume();

				float* aux_centroid = facet->getCentroid();
				centroid[0] = centroid[0] + aux_centroid[0];
				centroid[1] = centroid[1] + aux_centroid[1];
				centroid[2] = centroid[2] + aux_centroid[2];				
			}
			centroid[0] = centroid[0]/float((*it).size());
			centroid[1] = centroid[1]/float((*it).size());
			centroid[2] = centroid[2]/float((*it).size());
			
			if(volume > 7238.0){
				ofs << void_k << "\t" 
					<< centroid[0] << "\t" 
					<< centroid[1] << "\t" 
					<< centroid[2] << "\t"
					<< volume << "\n";
				++void_k;
			}
		}
	}
	ofs.close();
}









