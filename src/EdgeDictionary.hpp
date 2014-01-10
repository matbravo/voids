#ifndef __EDGEDICTIONARY__H
#define __EDGEDICTIONARY__H
#include <iostream>
#include "Dictionary.hpp"
#include "PointDictionary.hpp"
#include "Edge.hpp"
#include <map>
#include <utility>
#include <vector>
using namespace std;

class EdgeDictionary : public Dictionary<Edge>{
	private:
		map< pair< int, int> , Edge* > edgesDict1;
		vector< Edge* > edgesDict2;
		PointDictionary* pointsDict;
	public:
		EdgeDictionary();
		~EdgeDictionary();
		int add(Edge*);
		int add(int,int);
		void load(string){};
		Edge* getById(int);
		void setPointDictionary(PointDictionary*);
};




#endif