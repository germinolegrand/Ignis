#include "Ignis/log_system/ToString.h"
#include <iostream>

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
	int tab[5] = {1, 2, 3, 4, 5};
	int* tab_first = &tab[0];
	hasToString test;	
	testClass test2;
	std::cout << ign::log::toString(test) << std::endl;
	std::cout << ign::log::toString(40.1547f) << std::endl;
	std::cout << ign::log::toString(test2) << std::endl;
	std::cout << ign::log::toString(tab) << std::endl;
	std::cout << ign::log::toString(tab_first) << std::endl;
	return 0;
}
