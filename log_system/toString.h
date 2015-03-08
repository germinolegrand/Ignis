#pragma once

#include <string>
#include <type_traits>
#include <sstream>
#include <tuple>
#include <typeinfo>
#include <cxxabi.h>

namespace ign {
namespace log {
////////////////////////////////////////////
// SFINAE tests
////////////////////////////////////////////

template <typename T>
class has_toString
{
	typedef char one;
	typedef long two;
	template <typename C> static one test( decltype(&C::toString) ) ;
	template <typename C> static two test(...);
public:
	enum { value = sizeof(test<T>(0)) == sizeof(char) };
};

// see : http://stackoverflow.com/questions/4347921/sfinae-compiler-troubles
template <typename T> 
class is_container
{
	// Is.
	template <typename U>
	static char test(U* u, 
			int (*b)[sizeof(typename U::const_iterator()==((U*)0)->begin())] = 0,
			int (*e)[sizeof(typename U::const_iterator()==((U*)0)->end())] = 0);
	// Is not.
	template <typename U> static long test(...);
public :
	enum { value = (1 == sizeof test<T>(0)) };
};

////////////////////////////////////////////
// Info
////////////////////////////////////////////
template<class T>
std::string getName(const T& obj, bool getRealName = true)
{
	std::string str = "obj";
	if (getRealName) {
		try {
			int status;
			char *realname = abi::__cxa_demangle(typeid(obj).name(), 0, 0, &status);
			str = realname;
			free(realname);
			
			//remove std::
			if (str.size() >= 5 && str.substr(0, 5) == "std::")
					str.erase(begin(str), begin(str)+5);
			
			//if it's a template, find < and cut everything behind it 
			//if it's more than 13 characters, cut to 10 and set ".." at the end
			auto it = str.find_first_of("<");
			if (it != std::string::npos) { 
				str.erase(begin(str)+it, end(str));
			}
		} catch(...) {
			str = "obj";
		}
	}

	return str;
}

////////////////////////////////////////////
// ToString
////////////////////////////////////////////

/** string **/
template<class T, std::enable_if_t<std::is_same<T, std::string>::value>* = nullptr>
std::string toString(const T& t)
{
	return t;
}

/** arithmetic **/
template<class T, std::enable_if_t<std::is_arithmetic<T>::value && !std::is_same<T, bool>::value >* = nullptr>
std::string toString(const T& t)
{
	return std::to_string(t);
}

/** boolean **/
template<class T, std::enable_if_t<std::is_same<T, bool>::value>* = nullptr>
std::string toString(const T& t)
{
	return t ? std::string{"True"} : std::string{"False"};
}

/** pair **/
template<class T, class U>
std::string toString(const std::pair<T, U>& p)
{
	return std::string("`" + toString(p.first) + " : " + toString(p.second) + "`");
}

/** pointer **/
template<class T, std::enable_if_t<std::is_pointer<T>::value>* = nullptr>
std::string toString(const T& t)
{
	std::stringstream ss;

	ss << "@" << t;

	return ss.str();
}

/** array with [] **/
template<class T, std::enable_if_t<std::is_array<T>::value>* = nullptr>
std::string toString(const T& t)
{
	std::string res = "[";

	for (const auto& elem : t)
		res += toString(elem) + ", ";

	if (res.size() > 2)
		res.erase(end(res)-2, end(res));
	res += "]";

	return res;
}

/** has_toString **/
template<class T, typename std::enable_if<has_toString<T>::value>::type* = nullptr>
std::string toString(const T& t)
{
	return t.toString();
}

/** is a container **/
template<class T, typename std::enable_if<is_container<T>::value>::type* = nullptr>
std::string toString(const T& t)
{
	std::string res = getName(t) + "{";

	for(const auto& val : t)
		res += toString(val) + ", ";
	
	if (res.size() > 2)
		res.erase(end(res)-2, end(res));
	res += "}";

	return res;
}

/** Other **/
template<class T, std::enable_if_t<std::is_class<T>::value && !has_toString<T>::value && !is_container<T>::value>* = nullptr>
std::string toString(const T& t)
{
	std::stringstream ss;
	ss << getName(t) << "@" << &t;
	return ss.str();
}

/** tuple **/
/*
template<typename Tuple, std::size_t remaining>
std::string __tupleToString(const Tuple& t)
{
	std::string res = toString(std::get<std::tuple_size<Tuple>::value - remaining>(t));	
	res += __tupleToString<Tuple, remaining-1>(t); 
	return res;
}

template<typename Tuple, 0>
std::string __tupleToString(const Tuple& t)
{
	return "";	
}

template<typename ...Args>
std::string toString(const std::tuple<Args...>& t)
{
	std::string res = "`";
	for (int i = 0; i < std::tuple_size<t>::value; ++i)
		res += toString(std::get<i>(t)) + ", ";

	if (res.size() > 2)
		res.erase(end(res)-2, end(res));
	res += "`";
	return __tupleToString<decltype(t), std::tuple_size<t>::value>(t);
}
*/
}
}
