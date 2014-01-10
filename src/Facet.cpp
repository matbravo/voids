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
	return this->pointsId;
}
void Facet::setPointsId(int _pointsId[4]){
	pointsId[0]=_pointsId[0];
	pointsId[1]=_pointsId[1];
	pointsId[2]=_pointsId[2];
	pointsId[3]=_pointsId[3];
}
int* Facet::getNeighboursId(){
	return this->neighboursId;
}
void Facet::setNeighboursId(int _neighboursId[4]){
	neighboursId[0]=_neighboursId[0];
	neighboursId[1]=_neighboursId[1];
	neighboursId[2]=_neighboursId[2];
	neighboursId[3]=_neighboursId[3];
}
int* Facet::getEdgesId(){
	return this->edgesId;
}
void Facet::setEdgesId(int _edgesId[4]){
	edgesId[0]=_edgesId[0];
	edgesId[1]=_edgesId[1];
	edgesId[2]=_edgesId[2];
	edgesId[3]=_edgesId[3];
	edgesId[4]=_edgesId[4];
	edgesId[5]=_edgesId[5];
}
void Facet::setEdgeDictionary(EdgeDictionary* _edgesDict){
	edgesDict = _edgesDict;
}
void Facet::setPointDictionary(PointDictionary* _pointsDict){
	pointsDict = _pointsDict;
}

/*float Facet::getLongestEdge(){
	return this->longestEdge;
}*/
/*void Facet::setLongestEdge(PointDictionary* pointsDict){
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
}*/

