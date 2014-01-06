#include "PointDictionary.hpp"
#include <fstream>
#include <stdlib.h>
#include <vector>
using namespace std;

PointDictionary::PointDictionary():Dictionary<int>(){

}

PointDictionary::~PointDictionary(){

}

void PointDictionary::load(string points_file){
	ifstream points_ifs(points_file.c_str());
	if(!points_ifs.good()){
		cout << "Error when tried to open '" << points_file << "'" << '\n';
	}else{
		// Using the second line to initialize the array
		string line;
		getline(points_ifs,line); 	// first line points' dimension
		getline(points_ifs,line);	// second line number of points
		int points_number = atoi(line.c_str());
		float* points[points_number];
		// Getting points in file
		for(int k = 0; k < points_number ; k++){
			getline(points_ifs,line);
			line.replace(line.length(),1,"\t");
			vector<string> line_splited = this->split(line,'\t');
			// Matrix column x y z in points[k]
			points[k] = new float[3];
			cout << k << "\t";
			for(vector<string>::iterator it = line_splited.begin(); it != line_splited.end() ; it++){
				cout << *it << " / " ;	
			}
			cout << "\n";
		}

	}
}

int* PointDictionary::getById(int id){
	return 0;
}