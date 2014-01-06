#include "FacetDictionary.hpp"
#include <fstream>
#include <stdlib.h>
#include <vector>
#include <thread>
using namespace std;

FacetDictionary::FacetDictionary(){}
FacetDictionary::~FacetDictionary(){}

Facet* FacetDictionary::getById(int id){
	return dict+id;
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
			dict = new Facet[facet_number1];
			// Read from files in two threads.
			thread first(&FacetDictionary::loadVertexes ,this , &vertexes_ifs , facet_number1);
			thread second(&FacetDictionary::loadNeighbours,this , &neighbours_ifs , facet_number2);
			first.join();
			second.join();
			vertexes_ifs.close();
			neighbours_ifs.close();
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
		dict[k].setNeighboursId(aux);
	}
}

void FacetDictionary::loadVertexes(ifstream *vertexes_ifs,int number){
	string line;
	// Getting vertexes' id in file
	for(int k = 0; k < number ; k++){
		getline(*vertexes_ifs,line);
		vector<string> line_splited = FacetDictionary::split(line,' ');
		int j = 0;
		int *aux = new int[4];
		for(vector<string>::iterator it = line_splited.begin()+1; it != line_splited.end() ; it++){ // first col : number of neighbours
			aux[j] = atoi((*it).c_str());
			j++;
		}
		dict[k].setPointsId(aux);
	}
}









