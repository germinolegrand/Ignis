#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <iostream>

#include "toString.h"

namespace ign {
namespace log {	

class basicLogger {
	class BadOutputFile{}; //exception class
public :
	bool show_time = false; //if activated, will print the time of the log (since start of the program)
	bool print_term = true; //if activated, will print in the terminal each time you call () operator
	std::string prefix = "[log]";
	std::string separator = " ";

protected :	
	std::string m_output_file; 
	std::ofstream m_output_stream;
	std::vector<std::string> m_buffer;

	template<class T, class ...Args>
	std::string write_arguments(const T& t, Args&&... args) const;

	template<class T>
	std::string write_arguments(const T& t) const;		

public :
	basicLogger(std::size_t buffer_size = 32);
	~basicLogger();
	//() operator
	template<typename ...Args>
	basicLogger& operator()(Args&&... args);
	
	//configure
	virtual basicLogger& configure(bool _print_term, const std::string& _prefix, const std::string& _separator, bool _print_time = false);
	
	//buffer size
	basicLogger& setBufferCapacity(std::size_t s); //if write is activated, each time the buffer is full it will write it in the file
	inline std::size_t getBufferCapacity() const { return m_buffer.capacity(); }

	//Output file
	inline basicLogger& setOutputFile(const std::string& path, bool truncate = true);
	inline std::string getOutputFile() const { return m_output_file; }

	//force write
	basicLogger& forceWrite(); //force write to the outputFile
};

basicLogger::basicLogger(std::size_t buffer_size)
{
	m_buffer.reserve(buffer_size);
}

basicLogger::~basicLogger()
{
	forceWrite();
	m_output_stream.close();
}

basicLogger& basicLogger::setBufferCapacity(std::size_t s)
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

basicLogger& basicLogger::forceWrite() 
{
	std::cout << "ForceWrite\n";
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

#include "basicLogger.inl"

}
}
