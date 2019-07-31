#ifndef __PLAYER_H__
#define __PLAYER_H__
#include "Unit.h"
namespace NspPlayer {
	static bool key[7];
	class Player :
		public Unit
	{
	public:
		Player();
		void Init();
		void Render();
		void Update();
		void Shot();
		int GetControl();

	public:

		int flag;       //flag
		PLAYER_STATE state;		//状态
		int power;      //power
		int point;      //点数
		int score;      //分数
		int num;        //残机数
		int invincible_cnt;  //无敌状态与计数变量
		int shot_mode;  //射击模式
		int money;      //金钱
		bool slow;       //是否缓慢移动
		int shot_cnt;    //射击的计数器
		SDL_Texture* center;

		SDL_Rect slow_center_size;
		SDL_Rect slow_center_rect;
		SDL_Point slow_center_point;


	};




}
#endif