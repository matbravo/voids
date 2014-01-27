#include "Facet.hpp"
#include <math.h>

Facet::Facet(){
	longestEdge = 0.0;
	volume = 0.0;
	voidId = -1;
}
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
float Facet::getLongestEdge(){
	if(this->longestEdge <= 0.0){
		float max_length = 0.0;
		for(int k= 0 ; k < 6 ; k++){
			float length = edgesDict->getById(edgesId[k]).getLength();
			if(length > max_length) max_length = length;
		}
		longestEdge = max_length;
	}
	return this->longestEdge;
}
float Facet::getVolume(){
	// Matrix result from vertex a,b,c and d
	// |(a-d).((b-d)x(c-d))|/6
	if(this->volume <= 0.0){
		float* a = pointsDict->getById(pointsId[0]);
		float* b = pointsDict->getById(pointsId[1]);
		float* c = pointsDict->getById(pointsId[2]);
		float* d = pointsDict->getById(pointsId[3]);
		float a_d[3];
		float b_d[3];
		float c_d[3];
		for(int k = 0 ; k < 3 ; k++){
			a_d[k] = a[k] - d[k];
			b_d[k] = b[k] - d[k];
			c_d[k] = c[k] - d[k];
		}
		// (b-d) x (c-d)
		float b_dXc_d[3];
		b_dXc_d[0] = b_d[1]*c_d[2] - c_d[1]*b_d[2];
		b_dXc_d[1] = c_d[0]*b_d[2] - b_d[0]*c_d[2];
		b_dXc_d[2] = b_d[0]*c_d[1] - c_d[0]*b_d[1];
		float result = float(a_d[0]*b_dXc_d[0]) + float(a_d[1]*b_dXc_d[1]) + float(a_d[2]*b_dXc_d[2]);
		result = float(result/6.0);
		if(result <= 0.0 ) result= float(result*-1.0);
		volume = result;
	}
	return this->volume;
}
float* Facet::getCentroid(){
	float* v1 = pointsDict->getById(pointsId[0]);
	float* v2 = pointsDict->getById(pointsId[1]);
	float* v3 = pointsDict->getById(pointsId[2]);
	float* v4 = pointsDict->getById(pointsId[3]);

	float result[3];
	result[0] = v1[0]+v2[0]+v3[0]+v4[0];
	result[1] = v1[1]+v2[1]+v3[1]+v4[1];
	result[2] = v1[2]+v2[2]+v3[2]+v4[2];

	centroid[0] = result[0]/4.0;
	centroid[1] = result[1]/4.0;
	centroid[2] = result[2]/4.0;

	return this->centroid;
}
int Facet::isInBorder(){
	for(int k = 0 ; k < 4 ; ++k){
		if(neighboursId[k] < 0 ) return 1;
	}
	return 0;
}
void Facet::reset(){
	longestEdge = 0.0;
	volume = 0.0;
}
int Facet::getVoidId(){
	return this->voidId;
}
void Facet::setVoidId(int _voidId){
	voidId = _voidId;
}






