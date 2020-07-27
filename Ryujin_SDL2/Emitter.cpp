/*
子弹发射器
每个Enemy有一个发射器，位置跟随单位
boss有一个或多个，变化多

更新发射器角度、位置等属性
弹幕从Bullet_pattern中选择
所有shoter对象的子弹均通过BulletManager管理


 */

#include "pch.h"
#include "Enemy.h"
#include "Emitter.h"
#include "Manager.h"

namespace NspEmitter {
	

	void(*EmitterBarrage[EMITTER_BARRAGE_MAX])(Emitter*) = {
			emitter_bullet_H000,emitter_bullet_H001,
			emitter_bullet_H002,emitter_bullet_H003,
			emitter_bullet_H004,emitter_bullet_H005,
			emitter_bullet_H006,emitter_bullet_H007,
			emitter_bullet_H008
	};
	void(*EmitterBossBarrage[EMITTER_BOSS_BARRAGE_MAX])(Emitter*) = {
			boss_shot_bulletH000
	};

	Emitter::Emitter()
	{
		this->state = EMITTER_STATE::DEFAULT;
		this->enemy_id = -1;
		this->flag = false;
		this->knd = 0;
		this->frame = 0;
		this->x = 0;
		this->y = 0;
		this->base_angle[0] = 0;
		this->base_spd[0] = 0;
		SDL_memset(this->bullet_id, false, sizeof(int) * BULLET_MAX);
		//this->bullet_id = new int[BULLET_MAX];

	}
	int Emitter::AddBulletID(int id) {
		bullet_id[id] = true;
		return 0;
	}

	void Emitter::Init(int enemy_id, int emitter_id, bool is_boss) {

		this->state = EMITTER_STATE::DEFAULT;
		SDL_memset(this->bullet_id, false, sizeof(int) * BULLET_MAX);
		this->id = emitter_id;
		this->enemy_id = enemy_id;
		this->is_boss = is_boss;
		if (is_boss) {
			this->x = boss->x;
			this->y = boss->y;
		}else if (enemy_id > 0) {
			this->x = enemy[enemy_id].x;
			this->y = enemy[enemy_id].y;
		}
		
		this->flag = true;
		this->frame = 0;
	}

	/*
	TODO:cpu占用
	*/
	void Emitter::Update() {
		
		if (is_boss) {
			if (boss->emitter_state[id] == EMITTER_STATE::CLEAR) { // 单位标记销毁此发射器
				Clear();
				return;
			}

			if (!boss->isExist())
				Clear(true); //Boss死亡，清空子弹
			else
				EmitterBossBarrage[boss->knd](this);
		}
		else {
			if (enemy[enemy_id].emitter_state == EMITTER_STATE::CLEAR) {// 单位标记销毁此发射器
				Clear();
				return;
			}

			if (!enemy[enemy_id].flag)	//所有者不存在，等待弹幕消失，然后销毁
				state = EMITTER_STATE::WAIT;
			else
				EmitterBarrage[enemy[enemy_id].blknd](this);
		}
		int bullet_num = 0;
		for (int i = 0; i < BULLET_MAX; i++) {
			if (bullet_id[i] && bullet[i].flag) {
				bullet_num++;
				bullet[i].x += cos(bullet[i].angle) * bullet[i].spd;
				bullet[i].y += sin(bullet[i].angle) * bullet[i].spd;
				//printf("cnt %d bullet x %lf y %lf angle %lf\n",frame, bullet[i].x, bullet[i].y, bullet[i].angle);
				bullet[i].frame++;
				if (bullet[i].x< (float)FX - 50 || bullet[i].x>(float)FMX + 50 || bullet[i].y< (float)FY - 50 || bullet[i].y>(float)FMY + 50) {//如果跑到画面外面的话
					if (bullet[i].till < bullet[i].frame) {//且比最低程度不会销毁的时间还要很长
						bullet[i].flag = false;//销毁之
						bullet_id[i] = false;
						//printf("bullet remove enemy_id:%d bullet_id:%d\n", enemy_id,i);
					}
				}
			}
		}
		//printf("%d\n", bullet_num);
		if (bullet_num == 0 && state == EMITTER_STATE::WAIT) {
			Clear();//所有者不存在，子弹为空
		}
			

		//printf("bullet num :%d\n", k);
		//查询当前显示中的子弹的熟练是否至少还有一个

		/*if (!enemy[enemy_id].flag) {
			flag = -1;//終了
			enemy[enemy_id].flag = false;
			//printf("cnt %d emitter remove enemy_id:%d\n", cnt,enemy_id);
		}*/

		frame++;

	}
	void Emitter::Clear(bool clear_bullet)
	{
		if(is_boss)
			boss->DestroyEmitter(id);
		this->flag = false;
		if (clear_bullet) {
			for (int i = 0; i < BULLET_MAX; i++) {
				if (bullet_id[i] && bullet[i].flag) {
					bullet[i].flag = false;
					bullet_id[i] = false;
				}
			}
		}
		
	}
}