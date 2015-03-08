#include "../log_system/toString.h"
#include <iostream>
#include <vector>
#include <unordered_map>

class hasToString
{
	public:
	std::string toString() const{ return std::string("It works"); };
};

class testClass 
{
	public:
	int test = 5;
};

int main() 
{
	std::vector<bool> vect = {true, true, false, true, false, true};
	std::unordered_map<std::string, int> test_map;
	test_map["bite"] = 5;
	test_map["couille"] = 8;
	test_map["truc"] = 20;

	int tab[5] = {1, 2, 3, 4, 5};
	int* tab_first = &tab[0];
	hasToString test;	
	testClass test2;

	std::cout << ign::log::toString(test) << std::endl;
	std::cout << ign::log::toString(40.1547f) << std::endl;
	std::cout << ign::log::toString(test2) << std::endl;
	std::cout << ign::log::toString(tab) << std::endl;
	std::cout << ign::log::toString(tab_first) << std::endl;
	std::cout << "test on std::vector : " << ign::log::toString(vect) << std::endl;
	std::cout << "test on std::map : " << ign::log::toString(test_map) << std::endl;
	//std::cout << "test on std::tuple : " << ignl::log::toString(test_tuple) << std::enl;
	return 0;
}
