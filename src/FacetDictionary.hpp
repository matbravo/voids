#ifndef __FACETDICTIONARY__H
#define __FACETDICTIONARY__H
#include <iostream>
#include "Dictionary.hpp"
#include "Facet.hpp"
#include "Edge.hpp"
#include "PointDictionary.hpp"
#include "EdgeDictionary.hpp"
#include <fstream>

using namespace std;

class FacetDictionary : public Dictionary<Facet>{
	private:
		Facet** facetsDict;
		EdgeDictionary* edgesDict;
		PointDictionary* pointsDict;
		void loadNeighbours(ifstream*,int);
		void loadVertexesAndEdges(ifstream*,int);
	public:
		FacetDictionary();
		~FacetDictionary();
		void load(string);
		Facet* getById(int);
		void setPointDictionary(PointDictionary*);
		void setEdgeDictionary(EdgeDictionary*);
		EdgeDictionary* getEdgeDictionary();
		int add(Facet*);
};

#endif