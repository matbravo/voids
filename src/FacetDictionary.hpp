#ifndef __FACETDICTIONARY__H
#define __FACETDICTIONARY__H

#include "Dictionary.hpp"
#include "Facet.hpp"
#include "PointDictionary.hpp"
#include <fstream>

class FacetDictionary : public Dictionary<Facet>{
	private:
		Facet* dict;
		void loadNeighbours(ifstream*,int);
		void loadVertexes(ifstream*,int);
		void reloadFacetData();
		PointDictionary* pointsDict;
	public:
		FacetDictionary();
		~FacetDictionary();
		void load(string);
		Facet* getById(int);
		void setPointDictionary(PointDictionary*);
};

#endif