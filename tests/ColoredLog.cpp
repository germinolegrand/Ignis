#include "../log/Logger.h"
#include <iostream>
#include <vector>
#include <unordered_map>

//g++ -Wall -std=c++14 LogConfig.cpp -o testLogConfig

using namespace ign;

int main()
{
	log::Logger logger;
	logger.cfg.mode = log::Config::W_TIME | log::Config::W_TERM | log::Config::W_THREAD_ID;
	logger.cfg.configure("[test]", " - ");
	logger.cfg.setStdOut(std::cout);

	logger(logger.cfg);
	logger(logger.style);

	std::cout << "test" << std::endl;

	return 0;
}
