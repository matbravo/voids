#include "AnalysisCriteria3.hpp"
#include <algorithm>
#include <vector>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include <iomanip>
#include <math.h>
#include "VoidContainer.hpp"


using namespace std;

AnalysisCriteria3::~AnalysisCriteria3(){}
AnalysisCriteria3::AnalysisCriteria3():VoidAnalyzer(){
	minVolume = 0.0;
	minPercentVolume = 0.0;
}
AnalysisCriteria3::AnalysisCriteria3(float _minVolume, float _minPercentVolume, float _minEdgeLength){
	minVolume = _minVolume;
	minPercentVolume = _minPercentVolume;
	minEdgeLength = _minEdgeLength;
}
bool AnalysisCriteria3::isBiggerThan(Edge a, Edge b){ 
	return (a.getLength() > b.getLength());
}

void AnalysisCriteria3::analyze(FacetDictionary *facetsDict){
	cout << "Analyzing ...\n";
	EdgeDictionary* edgesDict = facetsDict->getEdgeDictionary();

	vector<Edge> edgeList;

	for(int k=0 ; k < edgesDict->getDataLength() ; k++){
		Edge edgeAux = edgesDict->getById(k);
		if(edgeAux.getLength() >= this->minEdgeLength ){
			edgeList.push_back(edgeAux);
		}
	}

	sort(edgeList.begin(),edgeList.end(),&AnalysisCriteria3::isBiggerThan); // Complexity N log N

	VoidContainer* voidContainer = new VoidContainer();
	voidContainer->setFacetDictionary(facetsDict);

	int voidK = voidContainer->getNextId();
	float *volume = new float();

	for(vector<Edge>::iterator it = edgeList.begin(); it != edgeList.end() ; ++it){
		Edge edge = *it; // Actual edge
		vector<int> *singleVoid = new vector<int>(); // Facets' id of a single void
		*volume = 0.0;
		checkNeighbours(edge,facetsDict,singleVoid,volume,voidK); // Recursive algorithm to find voids
		if(singleVoid->size() > 0 && *volume > minVolume){
			voidContainer->addVoid(*singleVoid);
			voidK = voidContainer->getNextId();
		}else{
			for(vector<int>::iterator it = (*singleVoid).begin() ; it != (*singleVoid).end() ; ++it){
				facetsDict->setFacetVoidId(*it,-1);
			}
			delete singleVoid;
		}
	}

	delete volume;

	vector<int> voidsIdResult;
	voidsIdResult.push_back(0);

	int range = voidContainer->getDataLength();
	for(int k = 1 ; k < range ; k++){
		vector<int> voidsIdResult_aux;
		int voidSpace1 = k;
		for(vector<int>::iterator voidsIdResult_it = voidsIdResult.begin() ; voidsIdResult_it != voidsIdResult.end() ; ++voidsIdResult_it){
			int voidSpace2 = *voidsIdResult_it;
			int joinAns = joinVoids(voidSpace1,voidSpace2,voidContainer);
			if(joinAns < 0 ){
				voidsIdResult_aux.push_back(voidSpace2);
			}else{
				voidSpace1 = joinAns;
			}
		}
		voidsIdResult = voidsIdResult_aux;
		voidsIdResult.push_back(voidSpace1);
	}

	vector< vector<int> > preResult;
	for(vector<int>::iterator it = voidsIdResult.begin(); it != voidsIdResult.end() ; ++it){
		VoidSpace voidToAdd = voidContainer->getById(*it);
		if(	(voidToAdd.getVolume() > minVolume) &&
			(voidToAdd.isInBorder() == 0)
			){
			preResult.push_back(voidToAdd.getFacetsId());
		}
	}

	result = preResult;

	delete voidContainer;
}

void AnalysisCriteria3::checkNeighbours(Edge edge,FacetDictionary *facetsDict, vector<int> *voidResult,float *volume,int voidK){
	EdgeDictionary* edgesDict = facetsDict->getEdgeDictionary();
	vector< int> facetsId = edge.getFacetsId();

	// Get facets who share the same edge
	for(vector<int>::iterator it = facetsId.begin(); it != facetsId.end(); ++it){
		int facetId = *it;
		Facet facet = facetsDict->getById(facetId);
		if(*volume == 0.0){
			*volume = facet.getVolume();
		}
		// Algorithm's conditions for add facets in void result
		if( (facet.getVoidId() < 0) &&  // Facet not in a void
			(facet.getLongestEdge() == edge.getLength()) && // Actual edge is one of the longest edge of the facet
			(facet.getVolume()/(*volume)*100.0 >= minPercentVolume)
			){ 
			facetsDict->setFacetVoidId(facetId,voidK); // Set facet in void
			voidResult->push_back(facetId); // Add facet in result
			*volume += facet.getVolume();
			int* edgesId = facet.getEdgesId();
			for(int k = 0; k < 6 ; ++ k){
				if(edgesId[k] != edge.getId()){
					checkNeighbours(edgesDict->getById(edgesId[k]),facetsDict,voidResult,volume,voidK);
				}
			} 
		}
	}
}

int AnalysisCriteria3::joinVoids(int _void1,int _void2,VoidContainer* voidContainer){
	
	float area = 0.0;
	VoidSpace void1 = voidContainer->getById(_void1);
	VoidSpace void2 = voidContainer->getById(_void2);
	VoidSpace void_aux;

	if(void1.getFacetsId().size() > void2.getFacetsId().size()){
		void_aux = void1;
		void1 = void2;
		void2 = void_aux;
	}


	FacetDictionary *facetsDict = voidContainer->getFacetDictionary();

	vector<int> void1ids = void1.getFacetsId();
	vector<int> void2ids = void2.getFacetsId();

	for(vector<int>::iterator void1_it = void1ids.begin() ; void1_it != void1ids.end() ; ++void1_it){
		Facet facet1 = facetsDict->getById(*void1_it);
		int *aux = facet1.getNeighboursId();
		for(int k = 0 ; k < 4 ; ++k){
			if(aux[k] >= 0){ // If not in border
				Facet facet2 = facetsDict->getById(aux[k]);
				// if Facet2 in void2
				if(facet2.getVoidId() == void2.getId()){
					int *facet1_points = facet1.getPointsId();
					int *facet2_points = facet2.getPointsId();
					// Get the shared face
					int facePointsId[3];
					int pointsIdK = 0;
					for(int i = 0 ; i < 4 ; ++i){
						for(int j = 0 ; j < 4 ; ++j){
							if(facet1_points[i] == facet2_points[j]){
								facePointsId[pointsIdK] = facet1_points[i];
								++pointsIdK;
								break;
							}
						}
					}
					PointDictionary *pointsDict = facetsDict->getPointDictionary();
					float *a = pointsDict->getById(facePointsId[0]);
					float *b = pointsDict->getById(facePointsId[1]);
					float *c = pointsDict->getById(facePointsId[2]);
					area+=this->faceArea(a,b,c);
				}
			}
		}
	}

	
	float radioEqAreaInter = float(sqrt(area/(2.0*PI)));
	float radioEqVolume1 = pow((3.0/(4.0*PI))*void1.getVolume(),1.0/3.0);
	float radioEqVolume2 = pow((3.0/(4.0*PI))*void2.getVolume(),1.0/3.0);

	int retId = -1;
	if((radioEqAreaInter > radioEqVolume1*0.2) && (radioEqAreaInter > radioEqVolume2*0.2)){
		for(vector<int>::iterator it = void2ids.begin() ; it != void2ids.end() ; ++it){
			void1ids.push_back(*it);
		}
		voidContainer->deleteVoid(void1.getId());
		voidContainer->deleteVoid(void2.getId());
		retId = voidContainer->addVoid(void1ids);
	}	


	// Return -1 if no join took place. Else return new joined void
	return retId;

}


float AnalysisCriteria3::faceArea(float *a, float *b ,float *c){
	// Get the face's area |a-c x b-c| / 2
	// A-C
	float a_c[3];
	a_c[0] = a[0] - c[0];
	a_c[1] = a[1] - c[1];
	a_c[2] = a[2] - c[2];
	// B-C
	float b_c[3];
	b_c[0] = b[0] - c[0];
	b_c[1] = b[1] - c[1];
	b_c[2] = b[2] - c[2];

	float a_cXb_c[3];
	a_cXb_c[0] = a_c[1]*b_c[2] - b_c[1]*a_c[2];
	a_cXb_c[1] = a_c[2]*b_c[0] - b_c[2]*a_c[0];
	a_cXb_c[2] = a_c[0]*b_c[1] - b_c[0]*a_c[1];

	return float(sqrt(pow(a_cXb_c[0],2.0) + pow(a_cXb_c[1],2.0) + pow(a_cXb_c[2],2.0) )/2.0);
}






