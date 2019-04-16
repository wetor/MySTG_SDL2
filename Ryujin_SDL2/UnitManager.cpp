/*
单位管理者
管理包括[自机、敌人和BOSS]的动态多帧动画等
*/

#include "pch.h"
#include "define.h"
#include "global.h"
#include "Manager.h"

Player *player = NULL;
Enemy* enemy = new Enemy[ENEMY_MAX];
//list<Enemy*> enemy;
list<enemy_order_t> enemy_order;

void PlayerInit() {
	player = new Player();
	player->Init();
}
void EnemyInit() {
	enemy = new Enemy[ENEMY_MAX];

}
inline int search_enemy() {
	for (int i = 0; i < ENEMY_MAX; i++) {
		if (!enemy[i].isExist())
			return i;
	}
	return -1;
}
void EnemyEnter() {
	int emitter_id;
	for (auto _enemy_order = enemy_order.begin(); _enemy_order != enemy_order.end(); _enemy_order++) {
		if (_enemy_order->cnt == frame_total) {
			int k = search_enemy();
			if (k != -1) {
				enemy[k].Init(*_enemy_order);
				emitter_id = EmitterEnter(k);
				enemy[k].SetEmitter(emitter_id);
			}

		}
	}
}
void EnemyUpdate() {
	EnemyEnter();
	for (int i = 0; i < ENEMY_MAX; i++) {
		if (enemy[i].isExist()) {
			enemy[i].Update();
			//emitter[enemy[i].emitter_id].Update();
			
		}
	}

}
void EnemyDraw() {
	for (int i = 0; i < ENEMY_MAX; i++) {
		if (enemy[i].isExist()) {
			enemy[i].Draw();
		}
	}
}