#ifndef __FACET__H
#define __FACET__H
#include <iostream>
using namespace std;

class Facet{
	private:
		int id;
		int points[4];
		int neighbours[4];
	public:
		Facet(int,int[],int[]);
		int* getPointsId();
		void setPointsId(int[]);
		int* getNeighboursId();
		void setNeighboursId(int[]);
		int getId();
		void setId(int);
};

#endif