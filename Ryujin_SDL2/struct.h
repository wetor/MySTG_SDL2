#pragma once
#include <iostream>
#include <SDL.h>
#include <SDL_mixer.h>
#include "define.h"

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
	float x, y, angle, spd, base_angle[1], rem_spd[1], vx, vy;
	//旋转
	int rotate;
	int eff_detail;
};

//消灭特效
struct del_effect_t {
	int flag, cnt, col;
	float x, y;
};

//特效
struct effect_t {
	int flag, wait=0, col=0, knd, eff, brt=0;
	std::string img;
	float x=0, y=0, r=0, ang, spd, mvang;
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


//和Boss射击相关的结构体
struct boss_shot_t {
	//flag、种类、计数器、发射过来的敌人的编号、颜色
	int flag, knd, cnt, num;
	//基本角度、基本速度
	float base_angle[1], base_spd[1];
	//bullet_t bullet[BOSS_BULLET_MAX];
};

//用于物理计算的结构体
struct phy_t {
	int flag, cnt, set_t;
	float ax, v0x, ay, v0y, vx, vy, prex, prey;
};

//Boss的信息
struct boss_t {
	int flag, cnt, knd, wtime, state, endtime, hagoromo, graph_flag;
	int hp, hp_max;
	int sc_num;
	int *sc_enter,*sc_hp, *sc_knd, *sc_bg;

	float x, y, ang, spd;
	phy_t phy;
};

enum class RESOURCES_TYPE {
	DATA,
	IMAGE,
	SOUND,
	SCRIPT
};
//资源结构体
struct resources_t {
	RESOURCES_TYPE type;
	std::string filename;
	std::string name;
	int size;
};

enum class EMITTER_STATE {
	DEFAULT,	//默认状态，正常绑定
	WAIT,	//拥有者不存在，不再继续添加弹幕，等待剩余弹幕消失
	CLEAR	//清理所有弹幕，销毁拥有者
};

struct image_t {
	int width;
	int height;
	SDL_Surface* surface;
	SDL_Texture* texture;
};

enum class UNIT_TYPE{
	DEFAULT,
	ENV,
	BULLET,
	BULLET_PLAYER,
	PLAYER,
	ENEMY,
	EFFECT,
	EFFECT_DEATH,
	EFFECT_BOMB,
	BOSS
};

enum class SOUND_TYPE {
	DEFAULT,
	BACK_MUSIC
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
enum class PLAYER_STATE {
	DEFAULT,		//默认状态
	INVINCIBLE_MOVE,	//无敌并且上升
	INVINCIBLE,	//无敌
	DEATH,		//死亡
	BOMB,		//BOMB
	DEATH_BOMB,		//决死
};

enum class BOSS_STATE {
	DEFAULT,		//默认状态
	WAITING,	//等待状态
	SHOOTING,	//射击状态
};
enum class KEY_CONTROL {
	UP,
	DOWN,
	LEFT,
	RIGHT,
	SHOT,
	BOMB,
	SLOW
};
