#include "../log_system/basicLogger.h"
#include <iostream>
#include <vector>
#include <unordered_map>

//g++ -Wall -std=c++14 basicLoggerTest.cpp -o testBasicLogger

using namespace ign;

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

	//tuple
	auto test_tuple = std::make_tuple("test", 15, true, "tuple test ?");	

	ign::log::basicLogger dbg(5); //set buffer size
	dbg.configure(true /*print in terminal*/, "[dbg]" /*prefix*/, " " /*separator*/, false /*print time*/);
	dbg.setOutputFile("dbg.log");
	dbg.setStdStream(std::cout);

	dbg(test, 40.1547f, tab, tab_first, vect, test_map, test_tuple);

	for (int i = 0; i < 12; ++i)
		dbg("attempt :", i);

	return 0;
}
