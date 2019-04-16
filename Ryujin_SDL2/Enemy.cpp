#include "pch.h"
#include "Enemy.h"
#ifdef DEBUG
#include <stdlib.h>
#endif


void(*enemy_pattern[ENEMY_PATTERN_MAX])(Enemy*) = {
		enemy_pattern0, enemy_pattern1, enemy_pattern2, enemy_pattern3, enemy_pattern4,
		enemy_pattern5, enemy_pattern6, enemy_pattern7, enemy_pattern8, enemy_pattern9,
		enemy_pattern10
};
Enemy::Enemy()
{
}


Enemy::~Enemy()
{
}

void Enemy::Init(enemy_order_t _enemy_order) {
	Unit::Load("enemy0");
	w = 32;
	h = 32;
	Unit::Init(UNIT_ENEMY);

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
	for (int j = 0; j < 6; j++)
		this->item_n[j] = _enemy_order.item_n[j];

	func_pattern = enemy_pattern[pattern];

}
void Enemy::Update() {
	if (!flag) return;

	
	enemy_pattern[pattern](this);
	x += cos(ang)*sp;
	y += sin(ang)*sp;
	x += vx;
	y += vy;
	frame_now = move_state * 3 + (frame % (FRAME_SPEED * 3)) / FRAME_SPEED;
	//如果敌人跑到画面外面了就销毁
	if (x < FX - w * 2 || x > FMX + w * 2 || y < FY - h * 2 || y > FMY + h * 2) {
		flag = false;
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

