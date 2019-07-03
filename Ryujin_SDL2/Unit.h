#pragma once

#include "global.h"

class Unit
{
public:
	Unit();
	void Load(string type);
	void Init(UNIT_TYPE unit_type = UNIT_DEFAULT);
	void Draw();
	void Update();
	UNIT_TYPE GetType() {return unit_type;};
	void Free();

public:
	UNIT_TYPE unit_type;		//类型

	int frame;					//帧计数器
	int frame_num;				//总帧数
	int frame_now;				//当前动画帧/序号
	SDL_Rect *frame_rect;		//帧区域(数组，下标为帧数)
	SDL_Surface *surface;       //图像
	SDL_Texture *texture;       //图像
	double x, y;				//坐标
	double angle;				//角度
	int w, h;					//帧宽高
	string type;				//图像类型
};

