#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "Facet.hpp"
#include "FacetDictionary.hpp"
#include "PointDictionary.hpp"
#include "AnalysisCriteria1.hpp"
#include <vector>
using namespace std;


/*	argv[1] = input_file_name
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

	// File name into string
	string input_file = string(argv[1]);		

	// Create points dictionary from file
	PointDictionary *pointsDict = new PointDictionary();
	pointsDict->load(input_file);

	// Create facets dictionary from file
	FacetDictionary *facetsDict = new FacetDictionary();
	facetsDict->load(input_file);
	facetsDict->setPointDictionary(pointsDict);

	VoidAnalyzer *analyzer1 = new AnalysisCriteria1();
	analyzer1->analyze(facetsDict);
	analyzer1->printResult(input_file,facetsDict);

	delete pointsDict;
	delete facetsDict;
	delete analyzer1;

}









