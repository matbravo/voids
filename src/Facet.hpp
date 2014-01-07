#ifndef __FACET__H
#define __FACET__H
#include <iostream>
#include "PointDictionary.hpp"
using namespace std;

class Facet{
	private:
		int id;
		int points[4];
		int neighbours[4];
		float longestEdge;
	public:
		Facet();
		Facet(int,int[4],int[4]);
		int* getPointsId();
		void setPointsId(int[4]);
		int* getNeighboursId();
		void setNeighboursId(int[4]);
		int getId();
		void setId(int);
		void setLongestEdge(PointDictionary*);
		float getLongestEdge();
};

#endif