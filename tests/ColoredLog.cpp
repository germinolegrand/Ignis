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

	logger.style.setColors(log::Color::Red, log::Color::Black);

	logger("Text Rouge sur FOND NOIR");
	logger(ign::os::osToString());
	return 0;
}
