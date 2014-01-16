#ifndef __POINTDICTIONARY__H
#define __POINTDICTIONARY__H
#include <iostream>
#include "Dictionary.hpp"


using namespace std;

class PointDictionary : public Dictionary<float*>{
	private:
		float** dict;
	public:
		PointDictionary();
		~PointDictionary();
		void load(string);
		float* getById(int);
		int add(float**);
};

#endif