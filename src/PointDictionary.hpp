#ifndef __POINTDICTIONARY__H
#define __POINTDICTIONARY__H
#include "Dictionary.hpp"

using namespace std;

class PointDictionary : public Dictionary<int>{
	private:
		int* dict[];
	public:
		PointDictionary();
		~PointDictionary();
		void load(string);
		int* getById(int);
};

#endif