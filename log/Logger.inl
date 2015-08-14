template<typename ...Args>
Logger& Logger::operator()(Args&&... args)
{
	m_buffer.emplace_back(cfg.getHeader() + write_arguments(std::forward<Args>(args)...)); 

	//if print_term is actived, print to terminal
	if (cfg.mode & Config::W_TERM)
		cfg.stream() << style.apply(m_buffer.back()) + "\n";

	//if buffer reached his capacity, forceWrite
	if (m_buffer.size() >= getBufferCapacity())
		forceWrite();
	
	return *this;
}

template<class T>
std::string Logger::write_arguments(const T& t) const	
{
	return toString(t);
}

template<class T, class ...Args>
std::string Logger::write_arguments(const T& t, Args&&... args) const
{
	return std::string(toString(t) + cfg.separator + write_arguments(std::forward<Args>(args)...));
}

/*
inline Logger& Logger::setOutputFile(const std::string& path, bool truncate)
{
	//write what was logged for the previous file
	forceWrite();
	m_output_stream.close();
	
	m_output_stream.open(path, truncate ? std::ofstream::trunc : std::ofstream::app);

	if (!m_output_stream)
		throw BadOutputFile{};

	return *this;
}
*/


