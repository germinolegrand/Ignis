#pragma once 

#include <string>
#include <type_traits>
#include <sstream>

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

/*
template <typename T>
class is_begin_defined
{
	typedef char one;
	typedef long two;

	template <typename C> static one test( decltype(begin(decltype(C)) ) ;
	template <typename C> static two test(...);

public:
	enum { value = sizeof(test<T>(0)) == sizeof(char) };
};
*/

////////////////////////////////////////////
// ToString
////////////////////////////////////////////

/** has_toString **/
template<class T, typename std::enable_if<has_toString<T>::value>::type* = nullptr>
std::string toString(const T& t)
{
	return t.toString();
}

/** arithmetic **/
template<class T, std::enable_if_t<std::is_arithmetic<T>::value>* = nullptr>
std::string toString(const T& t)
{
	return std::to_string(t);
}	

/** pointer **/
template<class T, std::enable_if_t<std::is_pointer<T>::value>* = nullptr>
std::string toString(const T& t)
{
	std::stringstream ss;
	ss << "ptr@" << t; 
	return ss.str();
}	

/** array with [] **/
template<class T, std::enable_if_t<std::is_array<T>::value>* = nullptr>
std::string toString(const T& t)
{
	std::string res = "[";

	for (const auto& elem : t)
		res += toString(elem) + ", ";
	res.pop_back();
	res.pop_back();
	res += "]";	

	return res; 
}

/** having a begin(class), end(class) defined **/


/** Other **/
template<class T, std::enable_if_t<std::is_class<T>::value && !has_toString<T>::value>* = nullptr>
std::string toString(const T& t)
{
	std::stringstream ss;
	ss << "obj@" << &t;
	return ss.str();
}	

}
}
