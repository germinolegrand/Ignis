#pragma once 

#include <string>

/** OS & ARCHITECTURE DETECTION *******
* Unix : 
*        IGN_OS_UNIX
* Linux :
*        IGN_OS_LINUX
* Apple : 
*        IGN_OS_APPLE
*        IGN_OS_IOS_SIMULATOR (ios under xcode)
*        IGN_OS_IOS (iphone / ipad / ...)
*        IGN_OS_OSX (macbooks / ...)
* Android :
*        IGN_OS_ANDROID
* Windows :
*        IGN_OS_WIN
*        IGN_OS_WIN_32
*        IGN_OS_WIN_64
*        IGN_OS_CYGWIN
* Architecture :
*        IGN_OS_64
*        IGN_OS_32
***************************************/

//Apple produts
#if defined(__APPLE__) && defined(__MACH__)
//osx / ios (darwin) is an unix based os
#define IGN_OS_APPLE
#define IGN_OS_UNIX
#include <TargetConditionals.h>
//ios on xcode
#if TARGET_IPHONE_SIMULATOR == 1
#define IGN_OS_IOS_SIMULATOR
//ios device
#elif TARGET_OS_IPHONE == 1
#define IGN_OS_IOS
//osx device
#elif TARGET_OS_MAC == 1
#define IGN_OS_OSX
#endif
#endif

//detect ANDROID
#if defined(__ANDROID__)
#define IGN_OS_ANDROID
#endif

//detect LINUX
#if defined(__linux__)
#define IGN_OS_LINUX
#endif

//detect UNIX System
#if !defined(_WIN32) && (defined(__unix__) || defined(__unix) || (defined(__APPLE__) && defined(__MACH__)))
#define IGN_OS_UNIX
#endif

//detect WINDOWS
#if defined(_WIN32) || defined(_WIN64)
#define IGN_OS_WIN
//architecture
#if defined(_WIN32)
#define IGN_OS_32
#define ING_OS_WIN_32
#else
#define IGN_OS_64
#define IGN_OS_WIN_64
#endif
#endif

//Windows with Cygwin
#if defined(__CYGWIN__) && !defined(_WIN32)
#define IGN_OS_CYGWIN
#endif

//Architecture check under gcc
#if __GNUC__
#if __x86_64__ || __ppc64__
#define IGN_OS_64
#else
#define IGN_OS_32 
#endif
#endif

namespace ign {
namespace os {

std::string osToString() noexcept {
	static std::string os;

	if (os.empty()) {
//os
//unix
#ifdef IGN_OS_UNIX
		os += "Unix ";
#endif
//linux
#ifdef IGN_OS_LINUX
		os += "Linux ";
#endif
//apple
#if defined(IGN_OS_APPLE)
#ifdef IGN_OS_IOS_SIMULATOR
		os += "iOS simulator ";
#elif defined(IGN_OS_IOS)
		os += "iOs ";
#else 
		os += "Mac OS X ";
#endif
#endif
//Windows
#ifdef IGN_OS_WIN
		os += "Windows ";
#endif
//Cygwin
#ifdef IGN_OS_CYGWIN
		os += "Cygwin ";
#endif
//architecture
#ifdef IGN_OS_32
		os += "32 bits";
#else 	
		os += "64 bits";
#endif	
	}

	return os;
}
}
}
