#ifndef __TOOLS_H__
#define __TOOLS_H__
#include <iostream>
#include <string>
#include <stdio.h>
#include <stdarg.h>
#include <SDL.h>
#include <map>
using namespace std;
extern	void NumberShow(int x, int y, string info, int num);
extern	void NumberShow(int x, int y, string info, double num);

static char str[512];
inline void LogA(const char* format, ...) {
	va_list va;
	va_start(va, format);
	vsnprintf(str, 512, format, va);
	printf("%s%s\n", "State: ", str);
	//cout << "State: " << str << endl;
	va_end(va);
}

class Timer {
public:
	static void Start();
	static void Start(string name);
	static int End();
	static int End(string name);
	static int Get(string name);
	static string Get(int index);
	static int Size();
private:
	
};



#endif

