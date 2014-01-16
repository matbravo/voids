#include "AnalysisCriteria1.hpp"
#include <algorithm>
#include <vector>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <stdlib.h>
#include <time.h>
#include <math.h>

using namespace std;

AnalysisCriteria1::AnalysisCriteria1():VoidAnalyzer(){}
AnalysisCriteria1::~AnalysisCriteria1(){}

vector < vector < int > > AnalysisCriteria1::getResult(){
	return this->result;
}
bool isBiggerThan(Edge a, Edge b){ 
	return (a.getLength() > b.getLength());
}

void AnalysisCriteria1::analyze(FacetDictionary *facetsDict){
	cout << "Analyzing ...\n";
	vector < vector < int > > voidsResult; // Facets id in voids
	EdgeDictionary* edgesDict = facetsDict->getEdgeDictionary();

	vector<Edge> edgeList(edgesDict->getDataLength()); // Edge list used by sort
	for(int k=0 ; k < edgesDict->getDataLength() ; k++){
		edgeList[k] = edgesDict->getById(k);
	}
	sort(edgeList.begin(),edgeList.end(),isBiggerThan); // Complexity N log N


	int *facetsInVoid= new int[facetsDict->getDataLength()]; // Array contains facets marked visited by analyze
	for(int i=0;i < facetsDict->getDataLength();++i){
			facetsInVoid[i] = 0;
		}

	for(vector<Edge>::iterator it = edgeList.begin(); it != edgeList.end() ; ++it){
		Edge edge = *it; // Actual edge
		vector<int> *singleVoid = new vector<int>(); // Facets' id of a single void
		float *volume = new float();
		*volume = 0.0;
		checkNeighbours(edge,facetsDict,singleVoid,facetsInVoid,volume); // Recursive algorithm to find voids
		if(singleVoid->size() > 0 ){
			// Delete if singleVoid is in border
			int isInBorder = 0;
			for(vector<int>::iterator singleVoid_it = singleVoid->begin(); singleVoid_it != singleVoid->end(); ++singleVoid_it){
				Facet facet = facetsDict->getById(*singleVoid_it);
				if(facet.isInBorder() == 1){
					isInBorder = 1;
					break;
				}
				//volume+=facetsDict->getById(*singleVoid_it).getVolume();
			}
			if( isInBorder == 0 && (*volume) > MIN_VOLUME){ // Add only if not in border
				voidsResult.push_back(*singleVoid);
				
			}else{
				delete singleVoid;
			}
		}else{
			delete singleVoid;
		}
		delete volume;
	}
	delete [] facetsInVoid;
	result = voidsResult;
}

void AnalysisCriteria1::checkNeighbours(Edge edge,FacetDictionary *facetsDict, vector<int> *voidResult, int *facetsInVoid, float* volume){
	EdgeDictionary* edgesDict = facetsDict->getEdgeDictionary();
	vector< int> facetsId = edge.getFacetsId();
	// Get facets who share the same edge
	for(vector<int>::iterator it = facetsId.begin(); it != facetsId.end(); ++it){
		int facetId = *it;
		Facet facet = facetsDict->getById(facetId);
		// Algorithm's conditions for add facets in void result
		if( (facetsInVoid[facetId] == 0) &&  // Facet not in a void
			(facet.getLongestEdge() == edge.getLength()) && // Actual edge is one of the longest edge of the facet
			(facet.getVolume()/(*volume)*100.0 >= MIN_PERCENT_VOLUME)
			){ 
			facetsInVoid[facetId] = 1; // Set facet in void
			voidResult->push_back(facetId); // Add facet in result
			(*volume) = (*volume) + facet.getVolume();
			int* edgesId = facet.getEdgesId();
			for(int k = 0; k < 6 ; ++ k){
				checkNeighbours(edgesDict->getById(edgesId[k]),facetsDict,voidResult,facetsInVoid,volume);
			} 
		}
	}
}

void AnalysisCriteria1::printResult(string filename, FacetDictionary* facetsDict){
	string outputFile = filename+string("_output.dat");
	ofstream ofs(outputFile.c_str());
	
	if(ofs.good()){
		//cout << "GOOOD\n";
		int void_k =0;
		for(vector< vector< int > >::iterator it = this->result.begin() ; it != this->result.end() ; ++it){
			float centroid[3];
			centroid[0] = 0.0;
			centroid[1] = 0.0;
			centroid[2] = 0.0;
			float volume = 0.0;
			for(vector<int>::iterator void_it = (*it).begin(); void_it != (*it).end() ; ++void_it){
				Facet facet = facetsDict->getById(*void_it);
				volume = volume + facet.getVolume();
				float* aux_centroid = facet.getCentroid();
				centroid[0] = centroid[0] + aux_centroid[0];
				centroid[1] = centroid[1] + aux_centroid[1];
				centroid[2] = centroid[2] + aux_centroid[2];
			}
			centroid[0] = centroid[0]/float((*it).size());
			centroid[1] = centroid[1]/float((*it).size());
			centroid[2] = centroid[2]/float((*it).size());
			float radio = float(pow((float(3.0/float(4.0*PI))*volume),float(1.0/3.0)));
			ofs << void_k << "\t" 
				<< setprecision(12) << centroid[0] << "\t" 
				<< centroid[1] << "\t" 
				<< centroid[2] << "\t"
				<< radio << "\t"
				<< volume << "\n";
			++void_k;
		}
	}
	ofs.close();
}
void AnalysisCriteria1::printResultOFF(string filename, FacetDictionary* facetsDict){
	string outputFile_geom = filename+string("_output.off");
	ofstream ofs_geom(outputFile_geom.c_str());

	srand(time(NULL));

	PointDictionary* p = facetsDict->getPointDictionary();

	if(ofs_geom.good()){
		ofs_geom << "\tOFF\n";
		int points_n = p->getDataLength();
		int faces_n = 0;

		for(vector< vector< int > >::iterator it = this->result.begin() ; it != this->result.end() ; ++it){
			faces_n+=(*it).size();
		}
		faces_n=faces_n*4;

		ofs_geom << " " << points_n << " " << faces_n << " 0\n";

		for(int k = 0 ; k < p->getDataLength() ; k++){
			float* point = p->getById(k);
			ofs_geom << setprecision(12) << point[0] << "\t" << point[1] << "\t" << point[2] << "\n";
		}

		for(vector< vector< int > >::iterator it = this->result.begin() ; it != this->result.end() ; ++it){
			int rgb[3];
			rgb[0] = rand() % 256;
			rgb[1] = rand() % 256;
			rgb[2] = rand() % 256;
			for(vector<int>::iterator void_it = (*it).begin(); void_it != (*it).end() ; ++void_it){
				Facet facet = facetsDict->getById(*void_it);
				cout << "Neighbour : " << facet.getNeighboursId()[0] << " "
						<< facet.getNeighboursId()[1] << " "
						<< facet.getNeighboursId()[2] << " "
						<< facet.getNeighboursId()[3] << "\n"; 
				int *points_aux = facet.getPointsId();
				ofs_geom << "3 " << points_aux[0] << " " << points_aux[1] << " " << points_aux[2] 
							<< " " << rgb[0] << " " << rgb[1] << " " << rgb[2] << "\n";
				ofs_geom << "3 " << points_aux[0] << " " << points_aux[1] << " " << points_aux[3] 
							<< " " << rgb[0] << " " << rgb[1] << " " << rgb[2] << "\n";
				ofs_geom << "3 " << points_aux[0] << " " << points_aux[2] << " " << points_aux[3] 
							<< " " << rgb[0] << " " << rgb[1] << " " << rgb[2] << "\n";
				ofs_geom << "3 " << points_aux[1] << " " << points_aux[2] << " " << points_aux[3] 
							<< " " << rgb[0] << " " << rgb[1] << " " << rgb[2] << "\n";
			}
		}
	}
	ofs_geom.close();

}









