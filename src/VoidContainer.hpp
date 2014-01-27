#ifndef __VOIDCONTAINER__H
#define __VOIDCONTAINER__H
#include <iostream>
#include "VoidSpace.hpp"
#include "FacetDictionary.hpp"
#include <map>
using namespace std;

class VoidContainer{
	private:
		map< int, vector<int> > voidsMap;
		int data_n;
		FacetDictionary* facetsDict;
	public:
		VoidContainer();
		~VoidContainer();
		int addVoid(vector<int>); // Add a new void and return Id
		void deleteVoid(int); // Delete void by Id
		VoidSpace getById(int);
		void setFacetDictionary(FacetDictionary*);
		FacetDictionary* getFacetDictionary();
		int getNextId(){ return this->data_n; }
		int getDataLength(){ return this->voidsMap.size(); }
};

#endif
