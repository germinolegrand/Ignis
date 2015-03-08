template<typename ...Args>
basicLogger& basicLogger::operator()(Args&&... args)
{
	m_buffer.emplace_back(prefix + (show_time ? "[time]" : "") + separator + write_arguments(std::forward<Args>(args)...) + "\n"); 

	//if print_term is actived, print to terminal
	if (print_term)
		std::cout << m_buffer.back();

	//if buffer reached his capacity, forceWrite
	if (m_buffer.size() >= getBufferCapacity())
		forceWrite();
	
	return *this;
}

template<class T>
std::string basicLogger::write_arguments(const T& t) const	
{
	return toString(t);
}

template<class T, class ...Args>
std::string basicLogger::write_arguments(const T& t, Args&&... args) const
{
	return std::string(toString(t) + separator + write_arguments(std::forward<Args>(args)...));
}

basicLogger& basicLogger::configure(bool _print_term, const std::string& _prefix, const std::string& _separator, bool _print_time)
{
	print_term = _print_term;
	show_time = _print_time;
	prefix = _prefix;
	separator = _separator;
	return *this;
}

inline basicLogger& basicLogger::setOutputFile(const std::string& path, bool truncate)
{
	//write what was logged for the previous file
	forceWrite();
	m_output_stream.close();
	
	m_output_stream.open(path, truncate ? std::ofstream::trunc : std::ofstream::app);

	if (!m_output_stream)
		throw BadOutputFile{};

	return *this;
}


