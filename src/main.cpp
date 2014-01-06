#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "Facet.hpp"
#include "PointDictionary.hpp"
#include <vector>
using namespace std;


vector<string> split(string,char);

/*	argv[0] = input_file_name
	Example:
		If you used the file called SDSS.dat SDSS_neighbours.dat SDSS_vertex.dat, input_file_name would be SDSS
*/			
int main(int argc, char **argv){

	/*
		Each file is written as follow:

			input.dat :=	x	y 	z
				- first line means number of dimensions.
				- second line means how many points has the file.
				- this file contains the data of points in the space with (x,y,z) in float format.

			input_neighbours.dat := number_of_neighbours neighbour_id_1 neighbour_id_2 neighbour_id_3 neighbour_id_4
				- first line means how many facets has the file.
				- this file contains the data of neighbours of an specific facet. File's line specifies the facet's id.

			input_vertex.dat := number_of_vertexes vertex_id_1 vertex_id_2 vertex_id_3 vertex_id_4
				- first line means how many facets has the file.			
				- this file contains the data of vertexes of an specific facet. File's line specifies the facet's id. 
	*/

	if(argc < 2){
		cout << "No input file specified" << '\n';
		return 0;
	}

	// Files names into strings
	string points_file = argv[1]+string(".dat");		
	string neightbours_file = points_file+string("_neighbours.dat");
	string vertex_file = points_file+string("_vertex.dat");

	// Crete points dictionary from file
	PointDictionary pointsDic;
	pointsDic.load(points_file);


	/*ifstream points_ifs(points_file.c_str());
	if(!points_ifs.good()){
		cout << "Error when tried to open '" << points_file << "'" << '\n';
		return 0;
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
			vector<string> line_splited = split(line,'\t');
			// Matrix column x y z in points[k]
			points[k] = new float[3];
			for(vector<string>::iterator it = line_splited.begin(); it != line_splited.end() ; it++){
				
			}
			//cout << "\n";
		}

	}*/

}

/*vector<string> split(string str, char token){
	vector<string> result;
	size_t begin = 0 ,found = 0;
	found = str.find(token,begin);
	while(found != string::npos){
		result.push_back(str.substr(begin,found-begin+1)); 
		begin = found+1;
		found = str.find(token,begin);
	}
	return result;
}*/

















