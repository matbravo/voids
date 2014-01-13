#include "Edge.hpp"
#include <math.h>

Edge::Edge(){}
Edge::Edge(int x, int y){
	pointsId[0] = x;
	pointsId[1] = y;
}
Edge::~Edge(){}


void Edge::setId(int _id){
	id=_id;
}
int Edge::getId(){
	return this->id;
}
void Edge::setPointsId(int _pointsId[2]){
	pointsId[0] = _pointsId[0];
	pointsId[1] = _pointsId[1];
}
int* Edge::getPointsId(){
	return this->pointsId;
}
void Edge::setFacetsId(vector<int> _facetsId){
	facetsId = _facetsId;
}
void Edge::addFacetId(int _facetId){
	facetsId.push_back(_facetId);
}
vector<int> Edge::getFacetsId(){
	return this->facetsId;
}
void Edge::setPointDictionary(PointDictionary* _pointsDict){
	pointsDict = _pointsDict;
}
void Edge::setLength(float _length){
	length=_length; 
}
float Edge::getLength(){
	if(this->length <= 0.0){
		float *point_j = pointsDict->getById(pointsId[0]);
		float *point_k = pointsDict->getById(pointsId[1]);
		length = sqrt(pow(point_j[0] - point_k[0],2) + pow(point_j[1] - point_k[1],2) + pow(point_j[2] - point_k[2],2));
	}	
	return this->length;
}
