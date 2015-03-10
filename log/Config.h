#pragma once

#include <string>
#include <iostream>

namespace ign 
{ namespace log {	

class Config {
	//Exceptions
	struct BadOutputStream{};  
	//Standard Stream
	std::ostream* m_stdout = &std::cout; 
public :
	enum Mode{ NO_MODE = 0, W_TERM = 1, W_TIME = 2, W_THREAD_ID = 4 };
	int mode = W_TERM;	

	std::string prefix    {"[log]"};
	std::string separator {""};
	std::string file_path {""}; //Output file path

	//configuration funcs
	inline Config& configure(const std::string& _prefix, const std::string& _separator) noexcept;
	
	Config& setStdOut(std::ostream& standardOut); //will throw BadStream if standardOut is not one of the standard c++ outputs
	std::ostream& stream() { return *m_stdout; }

	//utils
	std::string getHeader() const noexcept;

	//toString
	std::string toString() const noexcept;
};

inline Config& Config::configure(const std::string& _prefix, const std::string& _separator) noexcept {
	prefix = _prefix;
	separator = _separator;
	return *this;
}

Config& Config::setStdOut(std::ostream& s) {
	//check if s is one of the c++ standard output streams
	if (s.rdbuf() == std::cout.rdbuf() 
	|| s.rdbuf() == std::cerr.rdbuf()
	|| s.rdbuf() == std::clog.rdbuf())
		m_stdout = &s;
	else 
		throw BadOutputStream{};
		
	return *this;
}

std::string Config::getHeader() const noexcept {
	return prefix + (mode & W_THREAD_ID ? " T:" : "") + (mode & W_TIME ? "[time]" : "") + separator;
}

std::string Config::toString() const noexcept {
	std::string res = "log::Config";

	res += " prefix[" + prefix + "]";
	res += " separator[" + separator + "]";
	res += " file[" + file_path + "]";
	
	//write mode
	res += " mode[ ";
	if (mode == 0) {
		res += "NO_MODE ";
	} else {
		if (mode & W_TERM)
			res += "W_TERM ";
		if (mode & W_TIME)
			res += "W_TIME ";
		if (mode & W_THREAD_ID)
			res += "W_THREAD_ID ";
	}
	res += "]";

	//write stream
	res += " stream[";
	if (m_stdout->rdbuf() == std::cout.rdbuf())
		res += "std::cout";
	else if (m_stdout->rdbuf() == std::cerr.rdbuf())
		res += "std::cerr";
	else if (m_stdout->rdbuf()== std::clog.rdbuf())
		res += "std::clog";
	res += "]";

	return res;
}

} //log
} //ign
