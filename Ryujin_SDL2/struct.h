#pragma once
#include <iostream>
#include <SDL.h>
#include <SDL_mixer.h>
typedef struct {
	//计数器、移动模式、敌人的种类
	int cnt, pattern, knd;
	//初始化坐标和移动速度
	double x, y, sp;
	//弹幕开始时间、弹幕种类、颜色、体力、子弹的种类、停止时间、物品（6个种类）
	int bltime, blknd, col, hp, blknd2, wait, item_n[6];
}enemy_order_t;

//和子弹相关的结构体
typedef struct {
	//flag、种类、计数器、颜色、状态、保证不消失的最短时间、效果的种类
	int flag, knd, cnt, col, state, till, eff;
	//坐标、角度、速度、基本角度、瞬间记忆速度
	double x, y, angle, spd, base_angle[1], rem_spd[1];
}bullet_t;


//特效
typedef struct {
	int flag, wait, col, knd, eff, brt;
	double x, y, r=0, ang;
}effect_t;


//和角色射击相关的结构体
typedef struct {
	int flag, power, cnt, knd;//flag、power、计数器、种类
	double x, y, angle, spd;//坐标、角度、速度
}player_bullet_t;

enum RESOURCES_TYPE {
	RES_DATA,
	RES_IMAGE,
	RES_SOUND,
	RES_SCRIPT
};
//资源结构体
typedef struct {
	RESOURCES_TYPE type;
	std::string filename;
	std::string name;
	int size;
}resources_t;

enum EMITTER_STATE {
	EMITTER_DEFAULT,	//默认状态，正常绑定
	EMITTER_WAIT,	//拥有者不存在，不再继续添加弹幕，等待剩余弹幕消失
	EMITTER_CLEAR	//清理所有弹幕，销毁拥有者
};

typedef struct {
	int width, height;
	SDL_Surface* surface = NULL;
	SDL_Texture* texture = NULL;
}image_t;

enum UNIT_TYPE{
	UNIT_DEFAULT,
	UNIT_BULLET,
	UNIT_PLAYER_BULLET,
	UNIT_PLAYER,
	UNIT_ENEMY,
	UNIT_EFFECT,
	UNIT_BOSS
};

enum SOUND_TYPE {
	SOUND_DEFAULT,
	SOUND_BACK_MUSIC
};

typedef struct {
	SOUND_TYPE type;
	Mix_Chunk* sound;
	int volume = 50;
	int loops = 0;
}sound_t;