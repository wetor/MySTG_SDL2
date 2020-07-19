#include "pch.h"

#include "Tools.h"
#include "Manager.h"

void RenderText(int x, int y, SDL_Color col ,char* text) {
	SDL_Surface* surf = NULL;
	//TTF_RenderText_Solid
	surf = TTF_RenderText_Solid(font_mini, text, col);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surf);
	SDL_Rect dst = { x,y,surf->w,surf->h };
	SDL_RenderCopy(renderer, texture, NULL, &dst);
	SDL_FreeSurface(surf);
	SDL_DestroyTexture(texture);
}

//在x,y的位置显示数字
void NumberShow(int x, int y, TimerData data) {
	//printf("%d\n", y);
	static char text[30];
	snprintf(text, 30, "%-22s:[%2d]", data.name.c_str(), data.time);
	SDL_Color color = { 0,0,0,255 };
	if (data.type == "Draw")
		color = { 0,255,0,255 };// g
	else if (data.type == "Update")
		color = { 0,128,255,255 };//b
	

	RenderText(x, y, color ,text);
	
}
//在x,y的位置显示数字
void NumberShow(int x, int y, string info, int num) {

	static char text[30];
	snprintf(text, 30, "%-20s:[%4d]", info.c_str(), num);
	RenderText(x, y, SDL_Color({ 255, 128, 0, 255 }), text);

}
void NumberShow(int x, int y, string info, double num) {
	static char text[30];
	snprintf(text, 30, "%-18s:[%2.3f]", info.c_str(), num);
	RenderText(x, y, { 255, 0, 0,255 }, text);

}

Uint32 _time;
map<string, TimerData> table;
map<int, string> name_list;

void Timer::Start() {
	_time = SDL_GetTicks();
}
int Timer::End() {
	Uint32 t = _time;
	_time = SDL_GetTicks();
	return (int)(_time - t);
}
void Timer::Start(string name) {
	if (table.find(name) == table.end()) {
		table[name] = TimerData("default", name, SDL_GetTicks());
		name_list[name_list.size()] = name;
	}
	else {
		table[name].start = SDL_GetTicks();
	}
	
}
void Timer::Start(string type, string name) {
	
	if (table.find(type + name) == table.end()) {
		table[type + name] = TimerData(type, name, SDL_GetTicks());
		name_list[name_list.size()] = type + name;
	}
	else {
		table[type + name].start = SDL_GetTicks();
	}
	
}
int Timer::End(string name) {
	table[name].time = (int)(SDL_GetTicks() - table[name].start);
	return table[name].time;
}
int Timer::End(string type, string name) {
	return End(type + name);
}
TimerData Timer::Get(int index) {
	return table[name_list[index]];
}
TimerData Timer::Get(string name) {
	return table[name];
	
}
TimerData Timer::Get(string type, string name) {
	return table[type+name];
}
int Timer::Size() { 
	return name_list.size();
}