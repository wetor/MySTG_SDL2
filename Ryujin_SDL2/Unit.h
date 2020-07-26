#pragma once

#include "global.h"

class Unit
{
public:
	Unit();
	void Load(string type);
	void Init(UNIT_TYPE unit_type = UNIT_DEFAULT);
	void Render(int bright = 0, int alpha = 255, bool enable_bright = true);
	void Update();
	UNIT_TYPE GetType() {return unit_type;};
	void Free();

public:
	UNIT_TYPE unit_type;		//类型
	float range;					//圆形碰撞盒半径
	int frame;					//帧计数器
	int frame_num;				//总帧数
	int frame_now;				//当前动画帧/序号
	SDL_Rect* frame_rect;		//帧区域(数组，下标为帧数)
	SDL_Surface* surface;       //图像
	SDL_Texture* texture;       //图像
	SDL_Texture* mask_texture;	//遮罩，光
	float x, y;				//坐标
	float angle;				//角度
	float scale;				//缩放
	int w, h;					//帧宽高
	string type;				//图像类型
	SDL_FRect draw_rect;		//绘制区域
	SDL_FPoint draw_center;		//绘制旋转中心
	float draw_angle;			//绘制旋转角度
	float draw_w, draw_h;		//绘制的宽度、高度
};

