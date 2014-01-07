#include "Facet.hpp"
#include <math.h>

Facet::Facet(){}

Facet::Facet(int _id, int _points[4], int _neighbours[4]){
	this->setId(_id);
	this->setPointsId(_points);
	this->setNeighboursId(_neighbours);
}
int Facet::getId(){
	return this->id;
}
void Facet::setId(int _id){
	id=_id;
}
int* Facet::getPointsId(){
	return this->points;
}
void Facet::setPointsId(int _points[4]){
	points[0]=_points[0];
	points[1]=_points[1];
	points[2]=_points[2];
	points[3]=_points[3];
}
int* Facet::getNeighboursId(){
	return this->neighbours;
}
void Facet::setNeighboursId(int _neighbours[4]){
	neighbours[0]=_neighbours[0];
	neighbours[1]=_neighbours[1];
	neighbours[2]=_neighbours[2];
	neighbours[3]=_neighbours[3];
}
float Facet::getLongestEdge(){
	return this->longestEdge;
}
void Facet::setLongestEdge(PointDictionary* pointsDict){
	int *points_id = getPointsId();
	float max = 0.0;
	for(int k=0; k < 4 ; ++k){
		float* point_k = pointsDict->getById(points_id[k]);
		for(int j = k+1; j < 4; ++j){
			float* point_j = pointsDict->getById(points_id[j]);
			float result = sqrt(pow(point_j[0] - point_k[0],2) + pow(point_j[1] - point_k[1],2) + pow(point_j[2] - point_k[2],2));
			if(result > max) max = result;
		}
	}
	longestEdge = max;
}

