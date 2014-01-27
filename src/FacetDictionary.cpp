#include "FacetDictionary.hpp"
#include <fstream>
#include <stdlib.h>
#include <vector>
#include <thread>
using namespace std;

FacetDictionary::FacetDictionary(): Dictionary<Facet>(){
	edgesDict = new EdgeDictionary();
	data_n = 0;
}
FacetDictionary::~FacetDictionary(){
	delete edgesDict;
	for(int k = 0 ; k < data_n ; ++k){
		delete [] facetsNeighboursId[k];
		delete [] facetsPointsId[k];
		delete [] facetsEdgesId[k];
	}
	delete [] facetsNeighboursId;
	delete [] facetsEdgesId;
	delete [] facetsPointsId;
}
Facet FacetDictionary::getById(int id){
	Facet facet;
	facet.setId(id);
	facet.setPointsId(facetsPointsId[id]);
	facet.setNeighboursId(facetsNeighboursId[id]);
	facet.setEdgesId(facetsEdgesId[id]);
	facet.setEdgeDictionary(this->edgesDict);
	facet.setPointDictionary(this->pointsDict);
	facet.setVoidId(facetsVoidId[id]);
	return facet;
}
void FacetDictionary::load(string input_file){
	// Input files strings.
	string input_vertexes = input_file+string("_vertex.dat");
	string input_neighbours = input_file+string("_neighbours.dat");
	ifstream vertexes_ifs;
	vertexes_ifs.open(input_vertexes,ifstream::in);

	if(!vertexes_ifs.good()){
		cout << "Error when tried to open '" << input_file << "'" << '\n';
	}else{
		string line1;
		getline(vertexes_ifs,line1); // first line : number of facets
		int facet_number = atoi(line1.c_str());
		vertexes_ifs.close();
		facetsNeighboursId = new int*[facet_number];
		facetsEdgesId = new int*[facet_number];
		facetsPointsId = new int*[facet_number];
		facetsVoidId = new int[facet_number];
		for(int k = 0 ; k < facet_number ; k++){
			facetsVoidId[k] = -1;
		}
		data_n = facet_number;
		// Read from files into two threads.
		//thread first(&FacetDictionary::loadVertexesAndEdges,this,input_vertexes,facet_number);
		//thread second(&FacetDictionary::loadNeighbours,this,input_neighbours,facet_number);
		//second.join();
		//first.join();
		loadNeighbours(input_neighbours,facet_number);
		loadVertexesAndEdges(input_vertexes,facet_number);
	}
}
void FacetDictionary::loadNeighbours(string input_neighbours,int number){
	string line;
	ifstream neighbours_ifs;
	neighbours_ifs.open(input_neighbours,ifstream::in);
	if(!neighbours_ifs.good()){
		cout << "Error when tried to open '" << input_neighbours << "'" << '\n';
	}else{
		getline(neighbours_ifs,line);
		// Getting neighbours' id in file
		for(int k = 0; k < number ; k++){
			getline(neighbours_ifs,line);
			vector<string> line_splited = this->split(line,' ');
			int j = 0;
			int* aux = new int[4];
			for(vector<string>::iterator it = line_splited.begin()+1; it != line_splited.end() ; it++){ // first col : number of neighbours
				aux[j] = atoi((*it).c_str());
				j++;
			}
			//cout << "Neighbour : " << aux[0] << " " << aux[1] << " " << aux[2] << " " << aux[3] << "\n";
			facetsNeighboursId[k] = aux;
		}
		neighbours_ifs.close();
	}
	return;
}
// Load vertexes and edges to the dictionary
void FacetDictionary::loadVertexesAndEdges(string input_vertexes,int number){
	string line;
	ifstream vertexes_ifs;
	vertexes_ifs.open(input_vertexes,ifstream::in);
	if(!vertexes_ifs.good()){
		cout << "Error when tried to open '" << input_vertexes << "'" << '\n';
	}else{
		getline(vertexes_ifs,line); // first line number of facets
		// Getting vertexes' id in file
		for(int k = 0; k < number ; k++){
			getline(vertexes_ifs,line);
			vector<string> line_splited = this->split(line,' ');
			int j = 0;
			int *point_aux = new int[4];
			int *edge_aux = new int[6];
			for(vector<string>::iterator it = line_splited.begin()+1; it != line_splited.end() ; it++){ // first col : number of neighbours
				point_aux[j] = atoi((*it).c_str());
				j++;
			}
			
			// Add the edges
			int edge_k = 0;
			for (int i = 0 ; i < 4 ;i++){
				for(int j = i+1; j < 4 ; ++j){
					edge_aux[edge_k] = edgesDict->add(point_aux[i],point_aux[j],k); // Add Edge to edgesDicts
					edge_k++;
				}
			}
			//cout << "Vertex : " << point_aux[0] << " " << point_aux[1] << " " << point_aux[2] << "  " << point_aux[3] << "\n";
			facetsPointsId[k] = point_aux;
			facetsEdgesId[k] = edge_aux; 
		}
		vertexes_ifs.close();
	}
	return;
}
void FacetDictionary::setPointDictionary(PointDictionary* _pointsDict){
	pointsDict= _pointsDict;
	edgesDict->setPointDictionary(_pointsDict);
}
PointDictionary* FacetDictionary::getPointDictionary(){
	return this->pointsDict;
}
EdgeDictionary* FacetDictionary::getEdgeDictionary(){
	return edgesDict;
}
int FacetDictionary::add(Facet* _facet){
	return 0;
}
void FacetDictionary::setFacetVoidId(int facetId, int voidId){
	facetsVoidId[facetId] = voidId;
}





