#pragma once

#include <string>
#include <iostream>
#include "Color.h"
#include "toString.h"

namespace ign
{ namespace log {

struct Style {
	Color fg = Color::Default;
	Color bg = Color::Default;
	bool reverse{false};

	Style& setColors(const Color& foreground, const Color& background);
	std::string apply(const std::string& s) const noexcept;
	std::string toString() const noexcept;

	static bool inTerminal() noexcept;
private :
	static bool _term;
	static bool _checked;
};

bool Style::_term = false;
bool Style::_checked = false;

Style& Style::setColors(const Color& foreground, const Color& background) {
	fg = foreground;
	bg = background;
	return *this;	
}

std::string Style::apply(const std::string& s) const noexcept {
	if (!inTerminal())
		return s;
#ifdef IGN_OS_UNIX
	//ANSI escape code (http://en.wikipedia.org/wiki/ANSI_escape_code#graphics)
	return "\033[0" + ANSIEscapeCode(bg, true) + ";" + ANSIEscapeCode(fg) + "m" + s + "\033[0m"; 
#else 
#ifdef IGN_OS_WIN
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), getWindowsColor(fg) | getWindowsColor(bg, true));
	return s;
#endif	
#endif
}

std::string Style::toString() const noexcept {
	return "Style fg[" + log::toString(fg) + "] bg[" + 
			log::toString(bg) + "]" + (reverse? " Reverse Colors" : ""); 
}

bool Style::inTerminal() noexcept {
	if (!_checked) {
		_checked = true;
#ifdef IGN_OS_UNIX
		_term = isatty(fileno(stdout));
#else 	
#ifdef IGN_OS_WIN
		_term = _isatty(_fileno(stdout));
#endif
#endif
	}
	return _term;
}

} //log
} //ign
