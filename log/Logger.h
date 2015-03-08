#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <iostream>

#include "toString.h"

namespace ign {
namespace log {	

class Logger {
	class BadOutputFile{}; //exception class
public :
	bool show_time = false; //if activated, will print the time of the log (since start of the program)
	bool print_term = true; //if activated, will print in the terminal each time you call () operator
	std::string prefix = "[log]";
	std::string separator = " ";

protected :	
	std::ostream* m_std_stream = &(std::cout);
	std::string m_output_file; 
	std::ofstream m_output_stream;
	std::vector<std::string> m_buffer;

	template<class T, class ...Args>
	std::string write_arguments(const T& t, Args&&... args) const;

	template<class T>
	std::string write_arguments(const T& t) const;		

public :
	Logger(std::size_t buffer_size = 32);
	~Logger();
	//() operator
	template<typename ...Args>
	Logger& operator()(Args&&... args);
	
	//configure
	virtual Logger& configure(bool _print_term, const std::string& _prefix, const std::string& _separator, bool _print_time = false);
	
	//buffer size
	Logger& setBufferCapacity(std::size_t s); //if write is activated, each time the buffer is full it will write it in the file
	inline std::size_t getBufferCapacity() const { return m_buffer.capacity(); }

	//Output file
	inline Logger& setOutputFile(const std::string& path, bool truncate = true);
	inline std::string getOutputFile() const { return m_output_file; }

	//standard stream
	inline Logger& setStdStream(std::ostream& stream) { m_std_stream = &stream; return *this; }
	inline std::ostream& getStdStream() { return *m_std_stream; };

	//force write
	Logger& forceWrite(); //force write to the outputFile
};

Logger::Logger(std::size_t buffer_size)
{
	m_buffer.reserve(buffer_size);
}

Logger::~Logger()
{
	forceWrite();
	m_output_stream.close();
}

Logger& Logger::setBufferCapacity(std::size_t s)
{
	if (s == getBufferCapacity())	
		return *this;
	else if (s >= m_buffer.size())
		m_buffer.reserve(s);
	else //we have to remove elements 
	{
		//write all logs 
		forceWrite();
		//now m_buffer should be empty
		m_buffer.reserve(s);
	}

	return *this;
}

Logger& Logger::forceWrite() 
{
	if (m_output_stream.is_open())
	{
		//build the text
		std::string build;
		for (const auto& line : m_buffer)	
			build += line;
		
		//write to file
		m_output_stream << build;	
	}

	//clear buffer
	m_buffer.clear();

	return *this;
}

#include "Logger.inl"

}
}
