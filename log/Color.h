#pragma once

#include <string>
#include <iostream>
#include "../os/detect.h"
#include "toString.h"

//system dependent headers
#ifdef IGN_OS_UNIX
#include <unistd.h>
#elif defined(IGN_OS_WIN)
#include <Windows.h>
#include <io.h>
#endif

namespace ign
{ namespace log {

enum class Color : char {
	Black = 0,
	Red = 1,
	Blue = 2,
	Magenta = 3,
	Green = 4,
	Yellow = 5,
	Cyan = 6,
	White = 7,
	DarkGrey = 8,
	BrightRed = 9,
	BrightBlue = 10,
	BrightMagenta = 11,
	BrightGreen = 12,
	BrightYellow = 13,
	BrightCyan = 14,
	BrightGrey = 15,
	Default = 16
};

std::string toString(const Color& c){
	switch(c){
		case Color::Black :
			return "Black";
		case Color::Red :
			return "Red";
		case Color::Blue :	
			return "Blue";
		case Color::Magenta :
			return "Magenta";
		case Color::Green :
			return "Green";
		case Color::Yellow :
			return "Yellow";
		case Color::Cyan :
			return "Cyan";
		case Color::White :
			return "White";
		case Color::DarkGrey :
			return "DarkGrey";
		case Color::BrightRed :
			return "BrightRed";
		case Color::BrightBlue :
			return "BrightBlue";
		case Color::BrightMagenta :
			return "BrigthMagenta";
		case Color::BrightGreen :
			return "BrightGreen";
		case Color::BrightYellow :
			return "BrightYellow";
		case Color::BrightCyan :
			return "BrightCyan";
		case Color::BrightGrey :
			return "BrightGrey";
		case Color::Default :
			return "DefaultColor";
		default :	
			return "Unknown Color";
	}
}

//Used for unix based terms
std::string ANSIEscapeCode(const Color& c, bool background = false) {
	auto color = static_cast<int>(c);
	//default color 
	if (color == 16)
		return (background ? "49" : "39");
	//other colors
	return (color < 8 ? toString((background ? 40 : 30) + color) : toString((background ? 100 : 90) + color - 8));
}

#ifdef IGN_OS_WIN
_In_ getWindowsColor(const Color& c, bool background = false) {
	_In_ color;		
	return color;
}
#endif

} //log
} //ign
