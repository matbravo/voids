#include "VoidAnalyzer.hpp"
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <iomanip>

vector< vector< int > > VoidAnalyzer::getResult(){ 
	return this->result;
}
void VoidAnalyzer::printResult(string filename, FacetDictionary* facetsDict){
	string outputFile = filename+string("_output.dat");
	ofstream ofs(outputFile.c_str());
	if(ofs.good()){
		int void_k =0;
		for(vector< vector< int > >::iterator it = this->result.begin() ; it != this->result.end() ; ++it){
			float centroid[3];
			centroid[0] = 0.0;
			centroid[1] = 0.0;
			centroid[2] = 0.0;
			float volume = 0.0;
			for(vector<int>::iterator void_it = (*it).begin(); void_it != (*it).end() ; ++void_it){
				Facet facet = facetsDict->getById(*void_it);
				volume = volume + facet.getVolume();
				float* aux_centroid = facet.getCentroid();
				centroid[0] = centroid[0] + aux_centroid[0];
				centroid[1] = centroid[1] + aux_centroid[1];
				centroid[2] = centroid[2] + aux_centroid[2];
			}
			centroid[0] = centroid[0]/float((*it).size());
			centroid[1] = centroid[1]/float((*it).size());
			centroid[2] = centroid[2]/float((*it).size());
			float radio = float(pow((float(3.0/float(4.0*PI))*volume),float(1.0/3.0)));
			ofs << void_k << "\t" 
				<< setprecision(12) << centroid[0] << "\t" 
				<< centroid[1] << "\t" 
				<< centroid[2] << "\t"
				<< radio << "\t"
				<< volume << "\n";
			++void_k;
		}
	}
	ofs.close();
}
void VoidAnalyzer::printResultOFF(string filename, FacetDictionary* facetsDict){
	string outputFile_geom = filename+string("_output.off");
	ofstream ofs_geom(outputFile_geom.c_str());
	srand(time(NULL));
	PointDictionary* p = facetsDict->getPointDictionary();
	if(ofs_geom.good()){
		ofs_geom << "\tOFF\n";
		int points_n = p->getDataLength();
		int faces_n = 0;
		for(vector< vector< int > >::iterator it = this->result.begin() ; it != this->result.end() ; ++it){
			faces_n+=(*it).size();
		}
		faces_n=faces_n*4;
		ofs_geom << " " << points_n << " " << faces_n << " 0\n";
		for(int k = 0 ; k < p->getDataLength() ; k++){
			float* point = p->getById(k);
			ofs_geom << setprecision(12) << point[0] << "\t" << point[1] << "\t" << point[2] << "\n";
		}
		for(vector< vector< int > >::iterator it = this->result.begin() ; it != this->result.end() ; ++it){
			int rgb[3];
			rgb[0] = rand() % 256;
			rgb[1] = rand() % 256;
			rgb[2] = rand() % 256;
			for(vector<int>::iterator void_it = (*it).begin(); void_it != (*it).end() ; ++void_it){
				Facet facet = facetsDict->getById(*void_it);
				int *points_aux = facet.getPointsId();
				ofs_geom << "3 " << points_aux[0] << " " << points_aux[1] << " " << points_aux[2] 
							<< " " << rgb[0] << " " << rgb[1] << " " << rgb[2] << "\n";
				ofs_geom << "3 " << points_aux[0] << " " << points_aux[1] << " " << points_aux[3] 
							<< " " << rgb[0] << " " << rgb[1] << " " << rgb[2] << "\n";
				ofs_geom << "3 " << points_aux[0] << " " << points_aux[2] << " " << points_aux[3] 
							<< " " << rgb[0] << " " << rgb[1] << " " << rgb[2] << "\n";
				ofs_geom << "3 " << points_aux[1] << " " << points_aux[2] << " " << points_aux[3] 
							<< " " << rgb[0] << " " << rgb[1] << " " << rgb[2] << "\n";
			}
		}
	}
	ofs_geom.close();
}