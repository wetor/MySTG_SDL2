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
boss_t boss_data;

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
		boss_data.sc_num = 2;
		boss_data.sc_enter = new int[boss_data.sc_num] {100, -1};
		boss_data.sc_hp = new int[boss_data.sc_num] {5000, 10000};
		boss_data.sc_knd = new int[boss_data.sc_num] {4, 4 };
		boss_data.sc_bg = new int[boss_data.sc_num] {0, 1};


		boss_data.hagoromo = 0;//是否扇状扩散的flag
		boss_data.endtime = 99 * 60;//剩余时间
		boss_data.graph_flag = 0;//恢复绘制flag
		boss_data.wtime = 0;//初始化待机时间

		boss_data.x = FX + FW / 2.0f;//设置Boss的初始坐标
		boss_data.y = -30;
		//boss_data.knd = 0;//弹幕的种类

		boss->Init(boss_data);
	}
	void BossEnter() {
		if (!boss->isExist() && frame_total == boss->get_enter(0)) { //如果到了开始时间的话
			boss->Enter(0);
			//enter_boss(0);//开始
		}

	}
	void BossUpdate() {
		BossEnter();
		if (boss->isExist())
			boss->Update();

	}
	void BossRender() {
		if(boss->isExist())
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
				enemy[i].Clear();
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