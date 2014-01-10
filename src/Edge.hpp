#ifndef __EDGE__H
#define __EDGE__H
#include "PointDictionary.hpp"
#include <vector>
using namespace std;

class Edge{
	private:
		int id;
		int pointsId[2];
		vector<int> facetsId;
		float length;
		PointDictionary* pointsDict;
	public:
		Edge();
		Edge(int x, int y);
		~Edge();
		void setId(int);
		int getId();
		void setPointsId(int[2]);
		int* getPointsId();
		void setFacetsId(vector<int>);
		void addFacetId(int);
		vector<int> getFacetsId();
		void setLength(float);
		float getLength();
		void setPointDictionary(PointDictionary*);
};

#endif
