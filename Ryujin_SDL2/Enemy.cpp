#include "pch.h"
#include "Enemy.h"

#include <stdlib.h>


namespace NspEnemy {
	

	void(*enemy_pattern[ENEMY_PATTERN_MAX])(Enemy*) = {
			enemy_pattern0, enemy_pattern1, enemy_pattern2, enemy_pattern3, enemy_pattern4,
			enemy_pattern5, enemy_pattern6, enemy_pattern7, enemy_pattern8, enemy_pattern9,
			enemy_pattern10
	};

	Enemy::Enemy() : Unit()
	{
		this->flag = false;
		this->pattern = 0;
		this->move_state = 0;
		this->knd = 0;
		this->sp = 0;
		this->bltime = 0;
		this->blknd = 0;
		this->blknd2 = 0;
		this->col = 0;
		this->wait = 0;
		this->hp = 0;
		this->hp_max = 0;
		this->wait = 0;
		this->state = 0;
		this->vx = 0;
		this->vy = 0;
		this->ang = 0;
		this->back_col = 0;
		this->wtime = 0;
		this->item_n[0] = 0;
		func_pattern = NULL;
	}


	Enemy::~Enemy()
	{
	}

	void Enemy::Init(enemy_order_t _enemy_order) {
		Unit::Load("enemy0");
		Unit::Init(UNIT_TYPE::ENEMY);

		this->range = 16.0;

		this->flag = true;
		this->pattern = _enemy_order.pattern;
		this->move_state = 1;
		this->knd = _enemy_order.knd;
		this->x = _enemy_order.x;
		this->y = _enemy_order.y;
		this->sp = _enemy_order.sp;
		this->bltime = _enemy_order.bltime;
		this->blknd = _enemy_order.blknd;
		this->blknd2 = _enemy_order.blknd2;
		this->col = _enemy_order.col;
		this->wait = _enemy_order.wait;
		this->hp = _enemy_order.hp;
		this->hp_max = this->hp;
		this->vx = 0;
		this->vy = 0;
		this->ang = 0;
		this->back_col = 0;
		for (int j = 0; j < 6; j++)
			this->item_n[j] = _enemy_order.item_n[j];

		func_pattern = enemy_pattern[pattern];
		this->emitter_state = EMITTER_STATE::DEFAULT;

	}
	void Enemy::Update() {
		if (!flag) return;


		enemy_pattern[pattern](this);
		x += cos(ang) * sp;
		y += sin(ang) * sp;
		x += vx;
		y += vy;
		frame_now = move_state * 3 + (frame % (FRAME_SPEED * 3)) / FRAME_SPEED;
		//如果敌人跑到画面外面了就销毁
		if (x < (float)FX - w * 2 || x >(float)FMX + w * 2 || y < (float)FY - h * 2 || y >(float)FMY + h * 2) {
			Destroy();
			
			//printf("Enemy delete enemy_frame:%d game_frame:%d\n", frame,frame_total);
			//将被销毁
		}

		Unit::Update();
	}
	/*与Emitter建立连接*/
	void Enemy::Shot() {
		if (emitter_id == -1) return;
		//emitter[emitter_id].
	}
	void Enemy::Destroy(bool is_clear) {
		this->flag = false;
		if(is_clear)
			this->emitter_state = EMITTER_STATE::CLEAR;
			
		
	}
	bool Enemy::Death() {
		if (this->hp <= 0)
		{
			this->flag = false;
			return true;
		}
		return false;
	}
}