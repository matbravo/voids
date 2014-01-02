#include <iostream>
#include <fstream>
#include "Facet.hpp"
using namespace std;


/*	argv[0] = input_file_name
	Example:
		If you used the file called SDSS.dat SDSS_neighbours.dat SDSS_vertex.dat, input_file_name would be SDSS
*/	
int main(int argc, char **argv){


	/*
		Each file is written as follow:

			input.dat :=	x	y 	z
				-this file contains the data of points in the space with (x,y,z) in float format.

			input_neighbours.dat := number_of_neighbours neighbour_id_1 neighbour_id_2 neighbour_id_3 neighbour_id_4
				- this file contains the data of neighbours of an specific facet. File's line specifies the facet's id.

			input_vertex.dat := number_of_vertexes vertex_id_1 vertex_id_2 vertex_id_3 vertex_id_4
				- this file contains the data of vertexes of an specific facet. File's line specifies the facet's id. 
	*/

	string points = argv[1]+string(".dat");		
	string neightbours = points+string("_neighbours.dat");
	string vertex = points+string("_vertex.dat");

	ifstream points_file(points.c_str());
	if(!points_file.good()){
		cout << "Error when tried to open '" << points << "'" << '\n';
		return 0;
	}else{
		while(!points_file.eof()){
			string line;
			getline(points_file,line);
			cout << line << '\n' ;
		}
	}

}