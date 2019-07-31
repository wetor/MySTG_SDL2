#include "pch.h"

#include "Tools.h"
#include "Manager.h"

//在x,y的位置显示数字
void NumberShow(int x, int y, int num) {

	char text[10];
	snprintf(text, 10, "[%4d]", num);
	//printf(text);
	SDL_Surface* surf = NULL;
	//TTF_RenderText_Solid
	surf = TTF_RenderText_Solid(font_default, text, { 255, 0, 0,255 });
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surf);
	SDL_Rect dst = { x,y,surf->w,surf->h };
	SDL_RenderCopy(renderer, texture, NULL, &dst);
	SDL_FreeSurface(surf);
	SDL_DestroyTexture(texture);
	
	return;
}

