#pragma once
#include "Unit.h"
namespace NspEnemy {
	class Enemy :
		public Unit
	{
	public:
		Enemy();
		~Enemy();
		void Init(enemy_order_t _enemy_order);
		void Draw() { Unit::Draw(); };
		void Update();
		void Shot();
		bool isExist() { return flag; };
		void Destroy(bool is_clear = false);
		bool Death();
		void SetEmitter(int emitter_id)
		{
			this->emitter_id = emitter_id;
		}

	public:

		int emitter_id = -1;
		EMITTER_STATE emitter_state = EMITTER_DEFAULT;
		void(*func_pattern)(Enemy*);

		bool flag = false;
		//移动模式、方向、敌人的种类、HP最大值、掉落道具
		int  pattern, move_state, knd, hp, hp_max, item_n[6], back_col;;
		//速度x分量、速度y分量、速度、角度
		double vx, vy, sp, ang;
		//弹幕开始时间、弹幕的种类、弹的种类、颜色、状态、待机时间、停止时间
		int bltime, blknd, blknd2, col, state, wtime, wait;

	};


	void enemy_pattern0(Enemy*);
	void enemy_pattern1(Enemy*);
	void enemy_pattern2(Enemy*);
	void enemy_pattern3(Enemy*);
	void enemy_pattern4(Enemy*);
	void enemy_pattern5(Enemy*);
	void enemy_pattern6(Enemy*);
	void enemy_pattern7(Enemy*);
	void enemy_pattern8(Enemy*);
	void enemy_pattern9(Enemy*);
	void enemy_pattern10(Enemy*);

}