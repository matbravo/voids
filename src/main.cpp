#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "Facet.hpp"
#include "FacetDictionary.hpp"
#include "PointDictionary.hpp"
#include "AnalysisCriteria1.hpp"
#include "AnalysisCriteria2.hpp"
#include "AnalysisCriteria3.hpp"
#include <vector>
using namespace std;


/*	argv[1] = input_file_name
	Example:
		If you used the file called SDSS.dat SDSS_neighbours.dat SDSS_vertex.dat, input_file_name would be SDSS

	Example:
		./main SDSS_preprocess -v100000 -p1 -c3
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

	// File name into string
	string input_file = string(argv[1]);
	// Flag values
	float minVolume = 0.0;
	float minPercentVolume = 0.0;
	int criteria = 1;
	float minEdgeLength = 0.0;

	for(int k = 1 ; k < argc ; ++k ){
		if(argv[k][0] == '-'){
			switch(argv[k][1]){
				case 'v': 
					minVolume = atof(argv[k]+2);
					break;
				case 'p':
					minPercentVolume = atof(argv[k]+2);
					break;
				case 'c':
					criteria = atoi(argv[k]+2);
					break;
				case 'e':
					minEdgeLength = atof(argv[k]+2);
			}
		}else{
			input_file = string(argv[k]);
		}
	}

	// Create points dictionary from file
	PointDictionary *pointsDict = new PointDictionary();
	pointsDict->load(input_file);

	// Create facets dictionary from file
	FacetDictionary *facetsDict = new FacetDictionary();
	facetsDict->load(input_file);
	facetsDict->setPointDictionary(pointsDict);

	VoidAnalyzer *analyzer;

	switch(criteria){
		case 1:
			analyzer = new AnalysisCriteria1(minVolume,minPercentVolume);
			break;
		case 2:
			analyzer = new AnalysisCriteria2(minVolume,minPercentVolume,minEdgeLength);
			break;
		case 3:
			analyzer = new AnalysisCriteria3(minVolume,minPercentVolume,minEdgeLength);
			break;
	}

	analyzer->analyze(facetsDict);
	analyzer->printResult(input_file,facetsDict);
	analyzer->printResultOFF(input_file,facetsDict);

	delete pointsDict;
	delete facetsDict;
	delete analyzer;

}









