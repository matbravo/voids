#include "PointDictionary.hpp"
#include <fstream>
#include <stdlib.h>
#include <vector>
using namespace std;

PointDictionary::PointDictionary():Dictionary<float*>(){
	data_n = 0;
}
PointDictionary::~PointDictionary(){
	for(int k = 0 ; k< data_n ; ++k){
		delete [] dict[k];
	}
	delete [] dict;
}

float* PointDictionary::getById(int id){
	return dict[id];
}

int PointDictionary::add(float**){
	return 0;
}

void PointDictionary::load(string points_file){
	string input_points = points_file+string(".dat");
	ifstream points_ifs(input_points.c_str());
	if(!points_ifs.good()){
		cout << "Error when tried to open '" << points_file << "'" << '\n';
	}else{
		// Using the second line to initialize the array
		string line;
		getline(points_ifs,line); 	// first line : points' dimension
		getline(points_ifs,line);	// second line : number of points
		int points_number = atoi(line.c_str());
		data_n = points_number;
		dict = new float*[points_number];
		// Getting points in file
		for(int k = 0; k < points_number ; k++){
			getline(points_ifs,line);
			replace(line.begin(),line.end(),'\t',' ');
			vector<string> line_splited = this->split(line,' ');
			// Matrix column x y z in points[k]
			dict[k] = new float[3];
			int j = 0;
			for(vector<string>::iterator it = line_splited.begin(); it != line_splited.end() ; it++){
				if((*it).compare(" ") != 0){
					dict[k][j] = stof((*it).c_str());
					j++;
				}
			}
			//cout << dict[k][0] << " " << dict[k][1] << " " << dict[k][2] <<  "\n";
		}
		points_ifs.close();
	}
}

