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
void NumberShow(int x, int y, string info, int num) {

	static char text[26];
	snprintf(text, 26, "%-16s:[%4d]", info.c_str(), num);
	RenderText(x, y, num>=5 ? SDL_Color({ 0, 255, 0, 255 }) : SDL_Color({ 255, 0, 0,255 }),text);
	
}

void NumberShow(int x, int y, string info, double num) {
	static char text[26];
	snprintf(text, 26, "%-14s:[%2.3f]", info.c_str(), num);
	RenderText(x, y, { 255, 0, 0,255 }, text);

}

Uint32 _time;
map<string, int> time_table;
map<string, int> time_start;
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
	name_list[time_start.size()] = name;
	time_start[name] = SDL_GetTicks();
}
int Timer::End(string name) {
	Uint32 t = _time;
	_time = SDL_GetTicks();
	time_table[name] = (int)(_time - t);
	return time_table[name];
}
string Timer::Get(int index) {
	return name_list[index];
}
int Timer::Get(string name) {
	int t = time_table[name];
	if (t > 0) {
		time_table[name] = -1;
		return t;
	}
	else
		return 0;
	
}
int Timer::Size() { 
	return time_start.size();
}