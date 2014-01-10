#include "EdgeDictionary.hpp"

EdgeDictionary::EdgeDictionary(): Dictionary<Edge>(){}
EdgeDictionary::~EdgeDictionary(){}

int EdgeDictionary::add(Edge* _edge){
	return this->add(_edge->getPointsId()[0],_edge->getPointsId()[1]);

}

int EdgeDictionary::add(int x,int y){ // Edge without ID
	int pointsId[2] = {x,y}; 
	// Always keep lower point id as first value inside key map in edgesDict1
	if(pointsId[0] > pointsId[1]) {
		int id = pointsId[1];
		pointsId[1] = pointsId[0];
		pointsId[0] = id; 
	}
	// Search if _edge exists in edgesDict
	map< pair<int,int> , Edge* >::iterator it = edgesDict1.find(make_pair(pointsId[0],pointsId[1]));
	// If exist return edge->id
	if(it != edgesDict1.end()){
		return it->second->getId();
	}else{
	// Else data_n++ and return id;
		Edge *edge = new Edge();
		edge->setId(data_n);
		edge->setPointsId(pointsId);
		++data_n;
		edgesDict1.insert(make_pair(make_pair(pointsId[0],pointsId[1]),edge));
		edgesDict2.push_back(edge);
		return edge->getId();
	}
}

Edge* EdgeDictionary::getById(int _id){
	return edgesDict2[_id];
}

void EdgeDictionary::setPointDictionary(PointDictionary* _pointsDict){
	pointsDict = _pointsDict;
}