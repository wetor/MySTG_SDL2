#ifndef __TOOLS_H__
#define __TOOLS_H__
#include <iostream>
#include <string>
#include <stdio.h>
#include <stdarg.h>
#include <SDL.h>
#include <map>
using namespace std;
struct TimerData {
	TimerData() :type(""), name(""), time(0), start(0) {};
	TimerData(string type, string name, int start = 0, int time = 0) :type(type), name(name), time(start), start(time) {};

	TimerData operator=(TimerData data) {
		type = data.type;
		name = data.name;
		time = data.time;
		start = data.start;
		return *this;
	}
	string type;
	string name;
	int time;
	int start;
};



extern	void NumberShow(int x, int y, TimerData data);
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
	static void Start(string type, string name);
	static int End();
	static int End(string name);
	static int End(string type, string name);
	static TimerData Get(string name);
	static TimerData Get(string type, string name);
	static TimerData Get(int index);
	static int Size();
private:
	
};



#endif

