#include "PointDictionary.hpp"
#include <fstream>
#include <stdlib.h>
#include <vector>
using namespace std;

PointDictionary::PointDictionary():Dictionary<float>(){}
PointDictionary::~PointDictionary(){}

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
		dict = new float*[points_number];
		// Getting points in file
		for(int k = 0; k < points_number ; k++){
			getline(points_ifs,line);
			//line.replace(line.length(),1,"\t");
			vector<string> line_splited = this->split(line,'\t');
			// Matrix column x y z in points[k]
			dict[k] = new float[3];
			int j = 0;
			for(vector<string>::iterator it = line_splited.begin(); it != line_splited.end() ; it++){
				dict[k][j] = atof((*it).c_str());
				j++;
			}
		}
		points_ifs.close();
	}
}

float* PointDictionary::getById(int id){
	return dict[id];
}