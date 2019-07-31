#ifndef __TOOLS_H__
#define __TOOLS_H__
#include <iostream>
#include <string>
#include <stdio.h>
#include <stdarg.h>




static char str[512];
inline void LogA(const char* format, ...) {
	va_list va;
	va_start(va, format);
	
	vsnprintf(str, 512, format, va);
	printf("%s%s\n", "State: ", str);
	//cout << "State: " << str << endl;

	va_end(va);
	
}

#endif

