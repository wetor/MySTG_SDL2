/*
单位
包括敌人、BOSS、自机等多帧运动动画


*/

#include "pch.h"
#include "Unit.h"


Unit::Unit()
{
	this->unit_type = UNIT_DEFAULT;		//类型
	this->frame = 0;					//帧计数器
	this->frame_num = 0;				//总帧数
	this->frame_now = 0;				//当前动画帧/序号
	this->frame_rect = NULL;		//帧区域(数组，下标为帧数)
	this->surface = NULL;       //图像
	this->texture = NULL;       //图像
	this->x = 0;
	this->y = 0;				//坐标
	this->angle = 0;				//角度
	this->w = 0;
	this->h = 0;					//帧宽高
	this->type = "";				//图像类型
}
void Unit::Load(string type) {
	surface = image_map[type].surface;
	if (image_map[type].texture != NULL) {
		texture = image_map[type].texture;
	}
	else {
		texture = SDL_CreateTextureFromSurface(render, surface);
		image_map[type].texture = texture;
	}
	this->type = type;
	this->w = image_map[type].width;
	this->h = image_map[type].height;
}
void Unit::Init(UNIT_TYPE unit_type) {

	this->unit_type = unit_type;
	frame = 0;
	int t_h = surface->h / h;
	int t_w = surface->w / w;
	frame_num = t_h * t_w;
	frame_rect = new SDL_Rect[t_h * t_w];
	frame_now = 0;
	int k = 0;
	for (int i = 0; i < t_h; i++) {
		for (int j = 0; j < t_w; j++) {
			frame_rect[k++] = { j*w, i*h, w, h };
		}
	}
	angle = 0;
}
void Unit::Draw()
{
	/*TODO: 绘制单位，精度在此更改*/
	SDL_Rect *temp_rect = new SDL_Rect({ (int)(x + 0.5) - w / 2, (int)(y + 0.5) - h / 2, w, h });
	SDL_Point *temp_point = new SDL_Point({ (int)w / 2,(int)h / 2 });
	//SDL_RenderCopy(render, texture, &frame_rect[frame_now], temp_rect);
	double _angle = 0;
	if (unit_type == UNIT_BULLET || unit_type == UNIT_PLAYER_BULLET)
		_angle = angle * 180.0 / PI + 90.0;
	SDL_RenderCopyEx(render, texture, &frame_rect[frame_now], temp_rect, _angle, temp_point, SDL_FLIP_NONE);
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