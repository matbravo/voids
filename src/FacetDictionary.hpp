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
		int** facetsNeighboursId;
		int** facetsEdgesId;
		int** facetsPointsId;
		int* facetsVoidId;
		EdgeDictionary* edgesDict;
		PointDictionary* pointsDict;
		void loadNeighbours(string,int);
		void loadVertexesAndEdges(string,int);
	public:
		FacetDictionary();
		~FacetDictionary();
		void load(string);
		Facet getById(int);
		void setPointDictionary(PointDictionary*);
		PointDictionary* getPointDictionary();
		void setEdgeDictionary(EdgeDictionary*);
		EdgeDictionary* getEdgeDictionary();
		int add(Facet*);
		void setFacetVoidId(int,int); // Facet id , VoidId value
};

#endif