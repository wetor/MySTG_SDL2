/*
单位管理者
管理包括[自机、敌人和BOSS]的动态多帧动画等
*/

#include "pch.h"
#include "define.h"
#include "global.h"
#include "Manager.h"

NspPlayer::Player* player = new NspPlayer::Player();
NspBoss::Boss* boss = new NspBoss::Boss();
NspEnvironment::Environment* env = new NspEnvironment::Environment();
NspEnemy::Enemy enemy[ENEMY_MAX];
//list<Enemy*> enemy;
list<enemy_order_t> enemy_order;
bright_set_t bright_set; //绘制的亮度

namespace NspEnvironment {
	void EnvInit() {
		env->Init();
	}
	void EnvUpdate() {
		env->Update();

	}
	void EnvRender() {

		env->Render();
	}

}

namespace NspPlayer {
	void PlayerInit() {
		//player = new Player();
		player->Init();
	}
	void PlayerUpdate() {
		player->Update();

	}
	void PlayerRender() {
		player->Render();

	}
}

namespace NspBoss {
	void BossInit() {
		//boss->Init();
	}
	void BossEnter() {
		if (frame_total == boss->appear_count && !boss->isExist()) { //如果到了开始时间的话
			boss->Init(0);
			//enter_boss(0);//开始
		}
		if (boss->state == BOSS_STATE::SHOOTING && (boss->hp <= 0 || boss->endtime <= 0)) {//如果在弹幕中体力为0的话
			boss->Init(1);//进入下一次弹幕
		}
	}
	void BossUpdate() {
		BossEnter();
		boss->Update();

	}
	void BossRender() {
		boss->Render();

	}
}

namespace NspEnemy {
	
	void EnemyInit() {
		//enemy = new Enemy[ENEMY_MAX];
	}
	inline int search_enemy() {
		for (int i = 0; i < ENEMY_MAX; i++) {
			if (!enemy[i].isExist())
				return i;
		}
		return -1;
	}
	void EnemyEnter() {
		if (boss->isExist()) return;
		int emitter_id;
		for (auto _enemy_order = enemy_order.begin(); _enemy_order != enemy_order.end(); _enemy_order++) {
			if (_enemy_order->cnt == frame_total) {
				int k = search_enemy();
				if (k != -1) {
					enemy[k].Init(*_enemy_order);
					emitter_id = NspEmitter::EmitterEnter(k);
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
			}
		}
	}
	void EnemyRender() {
		for (int i = 0; i < ENEMY_MAX; i++) {
			if (enemy[i].isExist()) {
				enemy[i].Render();
			}
		}
	}
	void EnemyClear() {
		for (int i = 0; i < ENEMY_MAX; i++) {
			if (enemy[i].isExist()) {
				enemy[i].Destroy();
			}
		}
	}
#ifdef DEBUG
	void EnemyNumberShow(int x, int y) {
		int num = 0;
		for (int i = 0; i < ENEMY_MAX; i++) {
			if (enemy[i].isExist()) {
				num++;
			}
		}
		NumberShow(x, y,"Enemy num", num);
	}
#endif
}