#include "VoidContainer.hpp"
#include <utility>


VoidContainer::VoidContainer(){
	data_n = 0;
}
VoidContainer::~VoidContainer(){}

int VoidContainer::addVoid(vector<int> newVoid){
	voidsMap.insert(make_pair(data_n,newVoid));
	int ret = data_n;
	++data_n;
	for(vector<int>::iterator it = newVoid.begin() ; it != newVoid.end() ; ++it){
		facetsDict->setFacetVoidId(*it,ret);
	}
	return ret;
}
void VoidContainer::deleteVoid(int id){
	voidsMap.erase(id);
}
void VoidContainer::setFacetDictionary(FacetDictionary* _facetsDict){
	facetsDict = _facetsDict;
}
FacetDictionary* VoidContainer::getFacetDictionary(){
	return this->facetsDict;
}
VoidSpace VoidContainer::getById(int id){
	VoidSpace voidSpace;
	voidSpace.setId(id);
	voidSpace.setFacetsId(voidsMap[id]);
	voidSpace.setFacetDictionary(this->facetsDict);
	return voidSpace;
}