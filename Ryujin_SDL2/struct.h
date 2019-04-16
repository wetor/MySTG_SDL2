#pragma once

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
enum UNIT_TYPE{
	UNIT_BULLET,
	UNIT_PLAYER,
	UNIT_ENEMY,
	UNIT_BOSS,
	UNIT_DEFAULT
};

