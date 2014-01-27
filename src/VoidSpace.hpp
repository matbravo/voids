#ifndef __VOIDSPACE__H
#define __VOID__H
#include <iostream>
#include <vector>
#include "FacetDictionary.hpp"
using namespace std;


class VoidSpace{
	private:
		int id;
		vector<int> facetsId;
		FacetDictionary* facetsDict;
		float volume;
	public:
		VoidSpace();
		~VoidSpace();
		int getId();
		void setId(int);
		vector<int> getFacetsId();
		void setFacetsId(vector<int>);
		void setFacetDictionary(FacetDictionary*);
		FacetDictionary* getFacetDictionary();
		void addFacetId(int);
		float getVolume();
		int isInBorder();
};


#endif