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
		float longestEdge;
		float volume;
		float centroid[3];
		int voidId;
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
		int getVoidId();
		void setVoidId(int);
		float getLongestEdge();
		void setPointDictionary(PointDictionary*);
		void setEdgeDictionary(EdgeDictionary*);
		float getVolume();
		float* getCentroid();
		int isInBorder();
		void reset();
};

#endif