#include "EdgeDictionary.hpp"

EdgeDictionary::EdgeDictionary(): Dictionary<Edge>(){
	data_n = 0;
}
EdgeDictionary::~EdgeDictionary(){}

int EdgeDictionary::add(Edge* _edge){
	return 0;
}

int EdgeDictionary::add(int x,int y, int facetId){ // Edge without ID
	int pointsId[2];
	pointsId[0] = x;
	pointsId[1] = y; 
	// Always keep lower point id as first value inside key map in edgesDict1
	if(pointsId[0] > pointsId[1]) {
		int id = pointsId[1];
		pointsId[1] = pointsId[0];
		pointsId[0] = id; 
	}
	// Search if _edge exists in edgesDict
	map< pair<int,int> , int >::iterator it = edgesDict1.find(make_pair(pointsId[0],pointsId[1]));
	// If exist return edge->id
	if(it != edgesDict1.end()){
		edgesFacetsId[it->second].push_back(facetId);
		return it->second;
	}else{
	// Else data_n++ and return id;
		int returnId = data_n;
		edgesDict1.insert(make_pair(make_pair(pointsId[0],pointsId[1]),returnId));
		edgesDict2.push_back(make_pair(pointsId[0],pointsId[1]));
		vector<int> aux;
		aux.push_back(facetId);
		edgesFacetsId.push_back(aux);
		++data_n;
		return returnId;
	}
}

Edge EdgeDictionary::getById(int _id){
	Edge edge;
	edge.setId(_id);
	int pointsId[2] = {edgesDict2[_id].first,edgesDict2[_id].second};
	edge.setPointsId(pointsId);
	edge.setFacetsId(edgesFacetsId[_id]);
	edge.setPointDictionary(this->pointsDict);
	return edge;
}

void EdgeDictionary::setPointDictionary(PointDictionary* _pointsDict){
	pointsDict = _pointsDict;
}