#pragma once

#define DEBUG		//测试模式
#define MUTEX		//同步帧率锁
#define COLLIDER	//碰撞盒

//#define MUTEX		//是否开启互斥锁

#define PI			3.1415926535898
#define PI2			( PI * 2 )

#define	WINDOW_W	1152	//1920	* 0.6
#define	WINDOW_H	648		//1080	* 0.6

#define GAME_W		522		//870	* 0.6
#define GAME_H		624		//1040	* 0.6

#define BLANK_W		12
#define PANEL_W		( WINDOW_W - GAME_W - BLANK_W * 4 ) / 2

//左面板
#define LY		BLANK_W
#define	LH		( WINDOW_H - BLANK_W * 2 )
#define	LX		BLANK_W
#define LW		PANEL_W 

//游戏窗口
#define FY		BLANK_W
#define	FH		GAME_H
#define FMY		FY + FH
#define	FX		( LW + BLANK_W * 2 )
#define FW		GAME_W
#define FMX		FX + FW

//右面板
#define RY		BLANK_W
#define	RH		( WINDOW_H - BLANK_W * 2 )
#define	RX		( FX + FW + BLANK_W)
#define RW		PANEL_W


//Player
#define FRAME_SPEED	6


//一个敌人所拥有的最大子弹的数量
#define SHOT_BULLET_MAX 1000

//画面中一帧所能表示的最大的敌人的弹幕数
#define SHOT_MAX 30

//射击种类的最大数量
#define SHOT_KND_MAX 1

//效果音种类的的最大数量
#define SE_MAX 100

//敌人的行动模式的最大数量
#define ENEMY_PATTERN_MAX 11



//Enemy
#define ENEMY_MAX 30
//Bullet
#define BULLET_MAX 3000

//Emitter
#define EMITTER_MAX 60
#define EMITTER_BARRAGE_MAX 9


//自机射击的子弹的登录最大数
#define PLAYER_BULLET_MAX 200

//同时播放最多声音数
#define SOUND_MAX 100