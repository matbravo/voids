#include "VoidSpace.hpp"



VoidSpace::~VoidSpace(){}
VoidSpace::VoidSpace(){
	volume = 0.0;
	id = 0;
}

int VoidSpace::getId(){
	return this->id;
}
void VoidSpace::setId(int _id){
	id=_id;
}
vector<int> VoidSpace::getFacetsId(){
	return this->facetsId;
}
void VoidSpace::setFacetsId(vector<int> _facetsId){
	facetsId = _facetsId;
}
void VoidSpace::setFacetDictionary(FacetDictionary* _facetsDict){
	facetsDict = _facetsDict;
}
FacetDictionary* VoidSpace::getFacetDictionary(){
	return this->facetsDict;
}
void VoidSpace::addFacetId(int _id){
	facetsId.push_back(_id);
	facetsDict->setFacetVoidId(_id,this->id);
}
float VoidSpace::getVolume(){
	if(volume <= 0.0){
		for(vector<int>::iterator it = facetsId.begin() ; it != facetsId.end() ; ++it){
			volume+=(facetsDict->getById(*it)).getVolume();
		}
	}
	return this->volume;
}
int VoidSpace::isInBorder(){
	for(vector<int>::iterator it = facetsId.begin() ; it != facetsId.end() ; ++it){
		if(facetsDict->getById(*it).isInBorder() == 1){
			return 1;
		}
	}
	return 0;
}