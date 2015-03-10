#pragma once

#include <string>
#include <iostream>

namespace ign
{ namespace log {

//Color is supported on windows mac and linux
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
	BrightGrey = 15
};

std::string toString(const Color& c){
	switch(c){
		case Color::Black :
			return "Black";
		default :	
			return "Unknown Color";
	}
}

struct Style {
	Color fg_color = Color::White;
	Color bg_color = Color::Black;
	bool reverse_colors{false};

	std::string apply(const std::string& s) const noexcept;

	std::string toString() const noexcept {
		return "Style fg[" + log::toString(fg_color) + "] bg[" + 
				log::toString(bg_color) + "]" + (reverse_colors ? " Reverse Colors" : ""); 
	}
};

std::string Style::apply(const std::string& s) const noexcept {
	//TODO Apply style depending on the platform
	//on UNIX use ANSI escape code (http://en.wikipedia.org/wiki/ANSI_escape_code#graphics)
	std::string fgcode = "\e[31;1m";
	std::string bgcode = "";
	return bgcode + fgcode + s + "\e[0m"; //the last escape code resets all attributes 
}

} //log
} //ign
