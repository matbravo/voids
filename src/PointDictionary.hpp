#ifndef __POINTDICTIONARY__H
#define __POINTDICTIONARY__H
#include "Dictionary.hpp"

using namespace std;

class PointDictionary : public Dictionary<float>{
	private:
		float** dict;
	public:
		PointDictionary();
		~PointDictionary();
		void load(string);
		float* getById(int);
};

#endif