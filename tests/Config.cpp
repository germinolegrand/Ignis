#include "../log/Style.h"
#include "../log/Config.h"
#include <iostream>
#include <vector>
#include <unordered_map>

//g++ -Wall -std=c++14 LogConfig.cpp -o testLogConfig

using namespace ign;

int main()
{
	log::Config cfg;
	cfg.mode = log::Config::W_TIME | log::Config::W_TERM | log::Config::W_THREAD_ID;
	cfg.configure("[test]", " - ");
	cfg.setStdOut(std::clog);

	log::Config cfg2;
	cfg2.mode = log::Config::W_TERM | log::Config::W_THREAD_ID;
	cfg2.configure("[dbg]", " # ");
	cfg2.setStdOut(std::wcerr);

	std::cout << cfg.toString() << std::endl;
	std::cout << cfg2.toString() << std::endl;
	return 0;
}
