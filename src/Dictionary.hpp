#ifndef __DICTIONARY__H
#define __DICTIONARY__H
#include <iostream>
#include <vector>

using namespace std;

template<class T>
class Dictionary{
	protected:
		vector<string> split(string str, char token);
	public:
		Dictionary(){};
		~Dictionary(){};
		virtual void load(string) = 0;
		virtual T* getById(int) = 0;
};


template<class T> vector<string> Dictionary<T>::split(string str, char token){
	vector<string> result;
	size_t begin = 0 ,found = 0;
	found = str.find(token,begin);
	while(found != string::npos){
		result.push_back(str.substr(begin,found-begin+1)); 
		begin = found+1;
		found = str.find(token,begin);
	}
	return result;
}


#endif