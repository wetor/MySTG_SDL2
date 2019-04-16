/*
单位
包括敌人、BOSS、自机等多帧运动动画


*/

#include "pch.h"
#include "Unit.h"


Unit::Unit()
{
}
void Unit::Load(string type) {
	surface = image_surface[type];
	if (image_texture.find(type) != image_texture.end()) {
		texture = image_texture[type];
	}
	else {
		texture = SDL_CreateTextureFromSurface(render, surface);
		image_texture[type] = texture;
	}
	this->type = type;
}
void Unit::Init(UNIT_TYPE unit_type) {

	this->unit_type = unit_type;
	frame = 0;
	frame_num = (surface->w / w)*(surface->h / h);
	frame_rect = new SDL_Rect[frame_num];
	frame_now = 0;
	int k = 0;
	for (int i = 0; i < surface->h / h; i++) {
		for (int j = 0; j < surface->w / w; j++) {
			frame_rect[k++] = { j*w, i*h, w, h };
		}
	}
	angle = 0;
}
void Unit::Draw()
{

	SDL_Rect *temp_rect = new SDL_Rect({ (int)(x + 0.5) - w / 2, (int)(y + 0.5) - h / 2, w, h });
	SDL_Point *temp_point = new SDL_Point({ (int)w / 2,(int)h / 2 });
	//SDL_RenderCopy(render, texture, &frame_rect[frame_now], temp_rect);
	SDL_RenderCopyEx(render, texture, &frame_rect[frame_now], temp_rect, unit_type == UNIT_BULLET ? angle * 180.0 / PI + 90.0 : 0, temp_point, SDL_FLIP_NONE);
	delete temp_rect;
	delete temp_point;
}

void Unit::Update()
{
	frame++;

}
void Unit::Free() {
	surface = NULL;
	texture = NULL;
	delete frame_rect;

}