#include "FacetDictionary.hpp"
#include <fstream>
#include <stdlib.h>
#include <vector>
#include <thread>
using namespace std;

FacetDictionary::FacetDictionary(): Dictionary<Facet>(){
	edgesDict = new EdgeDictionary();
}
FacetDictionary::~FacetDictionary(){}

Facet* FacetDictionary::getById(int id){
	return facetsDict[id];
}

void FacetDictionary::load(string input_file){
	// Input files strings.
	
	string input_vertexes = input_file+string("_vertex.dat");
	string input_neighbours = input_file+string("_neighbours.dat");
	
	ifstream vertexes_ifs(input_vertexes);
	ifstream neighbours_ifs(input_neighbours);

	if(!vertexes_ifs.good() || !neighbours_ifs.good()){
		cout << "Error when tried to open '" << input_file << "'" << '\n';
	}else{
		string line1,line2;
		getline(vertexes_ifs,line1); // first line : number of facets
		getline(neighbours_ifs,line2);
		int facet_number1 = atoi(line1.c_str());
		int facet_number2 = atoi(line2.c_str());
		if(facet_number1 == facet_number2){
			facetsDict = new Facet*[facet_number1];
			for(int k = 0 ; k < facet_number1 ; ++k){
				facetsDict[k] = new Facet();
			}
			data_n = facet_number1;
			// Read from files in two threads.
			thread first(&FacetDictionary::loadVertexesAndEdges ,this , &vertexes_ifs , facet_number1);
			thread second(&FacetDictionary::loadNeighbours,this , &neighbours_ifs , facet_number2);
			first.join();
			second.join();
			vertexes_ifs.close();
			neighbours_ifs.close();
		}else{
			cout << "Length of files doesn't match" << "\n";
		} 
	}
}

void FacetDictionary::loadNeighbours(ifstream *neighbours_ifs,int number){
	string line;
	// Getting neighbours' id in file
	for(int k = 0; k < number ; k++){
		getline(*neighbours_ifs,line);
		vector<string> line_splited = FacetDictionary::split(line,' ');
		int j = 0;
		int *aux = new int[4];
		for(vector<string>::iterator it = line_splited.begin()+1; it != line_splited.end() ; it++){ // first col : number of neighbours
			aux[j] = atoi((*it).c_str());
			j++;
		}
		facetsDict[k]->setNeighboursId(aux);
	}
}

// Load vertexes and edges to the dictionary
void FacetDictionary::loadVertexesAndEdges(ifstream *vertexes_ifs,int number){
	string line;
	// Getting vertexes' id in file
	for(int k = 0; k < number ; k++){
		getline(*vertexes_ifs,line);
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
				edge_aux[edge_k] = edgesDict->add(point_aux[i],point_aux[j]); // Add Edge to edgesDict
				edgesDict->getById(edge_aux[edge_k])->addFacetId(k); // Add facet to FacetsId in Edge
				edge_k++;
			}
		}
		facetsDict[k]->setId(k);
		facetsDict[k]->setPointsId(point_aux);
		facetsDict[k]->setEdgesId(edge_aux);
		facetsDict[k]->setEdgeDictionary(this->edgesDict);
	}
}

void FacetDictionary::setPointDictionary(PointDictionary* _pointsDict){
	pointsDict= _pointsDict;
	for(int k=0 ; k < this->data_n ; k++){
		facetsDict[k]->setPointDictionary(_pointsDict);
	}
}

EdgeDictionary* FacetDictionary::getEdgeDictionary(){
	return edgesDict;
}

int FacetDictionary::add(Facet* _facet){
	return 0;
}





