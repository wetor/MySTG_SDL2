#ifndef __STRUCT_H__
#define __STRUCT_H__
#include <iostream>
#include <SDL.h>
#include <SDL_mixer.h>
struct enemy_order_t {
	//计数器、移动模式、敌人的种类
	int cnt, pattern, knd;
	//初始化坐标和移动速度
	float x, y, sp;
	//弹幕开始时间、弹幕种类、颜色、体力、子弹的种类、停止时间、物品（6个种类）
	int bltime, blknd, col, hp, blknd2, wait, item_n[6];
};

//和子弹相关的结构体
struct bullet_t {
	//flag、种类、计数器、颜色、状态、保证不消失的最短时间、效果的种类
	int flag, knd, cnt, col, state, till, eff;
	//坐标、角度、速度、基本角度、瞬间记忆速度
	float x, y, angle, spd, base_angle[1], rem_spd[1];
};

//消灭特效
struct del_effect_t {
	int flag, cnt, col;
	float x, y;
};

//特效
struct effect_t {
	int flag, wait=0, col=0, knd, eff, brt;
	std::string img;
	float x, y, r=0, ang, spd, mvang;
};
//Boom的信息
struct bom_t {
	int flag, cnt, knd;
	float x, y;
};

//咚！地晃动画面的信息
struct dn_t {
	int flag, cnt, time, size;
	int x, y;
};
//画面亮度的信息
struct bright_set_t {
	unsigned char brt;
};

//和角色射击相关的结构体
struct player_bullet_t {
	int flag, power, cnt, knd;//flag、power、计数器、种类
	float x, y, angle, spd;//坐标、角度、速度
};

enum RESOURCES_TYPE {
	RES_DATA,
	RES_IMAGE,
	RES_SOUND,
	RES_SCRIPT
};
//资源结构体
struct resources_t {
	RESOURCES_TYPE type;
	std::string filename;
	std::string name;
	int size;
};

enum EMITTER_STATE {
	EMITTER_DEFAULT,	//默认状态，正常绑定
	EMITTER_WAIT,	//拥有者不存在，不再继续添加弹幕，等待剩余弹幕消失
	EMITTER_CLEAR	//清理所有弹幕，销毁拥有者
};

struct image_t {
	int width;
	int height;
	SDL_Surface* surface;
	SDL_Texture* texture;
};

enum UNIT_TYPE{
	UNIT_DEFAULT,
	UNIT_ENV,
	UNIT_BULLET,
	UNIT_BULLET_PLAYER,
	UNIT_PLAYER,
	UNIT_ENEMY,
	UNIT_EFFECT,
	UNIT_EFFECT_DEATH,
	UNIT_EFFECT_BOMB,
	UNIT_BOSS
};

enum SOUND_TYPE {
	SOUND_DEFAULT,
	SOUND_BACK_MUSIC
};

struct sound_t {
	SOUND_TYPE type;
	Mix_Chunk* sound;
	int volume;
	int loops;
};

//子弹的信息
struct bullet_info_t {
	std::string id;
	int w, h, col_num;
	float range;
};
enum PLAYER_STATE {
	PLAYER_DEFAULT,		//默认状态
	PLAYER_DUEL,		//决死
	PLAYER_INVINCIBLE_MOVE,	//无敌并且上升
	PLAYER_INVINCIBLE,	//无敌
	PLAYER_DEATH		//死亡
};
enum KEY_CONTROL {
	UP,
	DOWN,
	LEFT,
	RIGHT,
	SHOT,
	BOMB,
	SLOW
};
#endif