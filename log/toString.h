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
std::string toString(const std::string& t)
{
	return t;
}

/** C style strings **/
std::string toString(const char* t)
{
	return std::string(t);
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
	return t ? "true" : "false";
}

/** pair **/
template<class T, class U>
std::string toString(const std::pair<T, U>& p)
{
	return "<" + toString(p.first) + ":" + toString(p.second) + ">";
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

	return std::move(res);
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
	std::string res = "[";

	for(const auto& val : t)
		res += toString(val) + ", ";

	if (res.size() > 2)
		res.erase(end(res)-2, end(res));
	res += "]";

	return std::move(res);
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

template<typename Tuple, std::size_t total, std::size_t remaining = total>
struct __tupleToString
{
    static
    void tupleToString(const Tuple& t, std::string& res)
    {
        res += toString(std::get<total - remaining>(t));
		res += ":";
        __tupleToString<Tuple, total, remaining-1>::tupleToString(t, res);
    }
};

template<typename Tuple, std::size_t total>
struct __tupleToString<Tuple, total, 1>
{
    static
    void tupleToString(const Tuple& t, std::string& res)
    {
        res += toString(std::get<total - 1>(t));
    }
};

template<typename Tuple, std::size_t total>
struct __tupleToString<Tuple, total, 0>
{
    static
    void tupleToString(const Tuple& t, std::string& res)
    {}
};

template<typename ...Args>
std::string toString(const std::tuple<Args...>& t)
{
	std::string res = "<";
	__tupleToString<decltype(t), std::tuple_size<std::remove_cv_t<std::remove_reference_t<decltype(t)>>>::value>::tupleToString(t, res);
	res += ">";
	return res;
}

}
}
