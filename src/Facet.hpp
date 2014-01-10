#ifndef __FACET__H
#define __FACET__H
#include <iostream>
#include "PointDictionary.hpp"
#include "EdgeDictionary.hpp"
using namespace std;

class Facet{
	private:
		int id;
		int pointsId[4];
		int neighboursId[4];
		int edgesId[6];
		PointDictionary* pointsDict;
		EdgeDictionary* edgesDict;
	public:
		Facet();
		Facet(int,int[4],int[4]);
		int getId();
		void setId(int);
		int* getPointsId();
		void setPointsId(int[4]);
		int* getNeighboursId();
		void setNeighboursId(int[4]);
		int* getEdgesId();
		void setEdgesId(int[6]);
		int getLongestEdgeId();
		void setPointDictionary(PointDictionary*);
		void setEdgeDictionary(EdgeDictionary*);
};

#endif