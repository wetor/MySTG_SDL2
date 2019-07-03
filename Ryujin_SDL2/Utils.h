#pragma once
#include <iostream>
#include <string>
#include <stdio.h>
#include <stdarg.h>

using namespace std;



inline void LogA(const char* format, ...) {
	va_list va;
	va_start(va, format);
	char* str = new char[512];
	vsnprintf(str, 512, format, va);
	va_end(va);
	cout << "State: " << str << endl;
	delete str;
}



