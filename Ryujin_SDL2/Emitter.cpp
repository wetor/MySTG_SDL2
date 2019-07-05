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
	

	void(*Emitter_barrage[EMITTER_BARRAGE_MAX])(Emitter*) = {
			emitter_bullet_H000,emitter_bullet_H001,
			emitter_bullet_H002,emitter_bullet_H003,
			emitter_bullet_H004,emitter_bullet_H005,
			emitter_bullet_H006,emitter_bullet_H007,
			emitter_bullet_H008
	};

	Emitter::Emitter()
	{
		this->state = EMITTER_DEFAULT;
		this->enemy_id = -1;
		this->flag = false;
		this->knd = 0;
		this->frame = 0;
		this->x = 0;
		this->y = 0;
		this->base_angle[0] = 0;
		this->base_spd[0] = 0;
		this->bullet_id_list = new int[BULLET_MAX];

	}
	int Emitter::AddBulletID(int id) {
		for (int i = 0; i < BULLET_MAX; i++) {
			if (bullet_id_list[i] < 0) {
				bullet_id_list[i] = id;
				break;
			}
		}
		return 0;
	}

	Emitter::~Emitter()
	{
		delete bullet_id_list;
	}
	void Emitter::Init(int enemy_id) {

		this->state = EMITTER_DEFAULT;
		for (int i = 0; i < BULLET_MAX; i++) bullet_id_list[i] = -1;
		this->enemy_id = enemy_id;
		this->x = enemy[enemy_id].x;
		this->y = enemy[enemy_id].y;
		this->flag = true;
		this->frame = 0;
	}

	/*
	TODO:cpu占用
	*/
	void Emitter::Update() {
		int i;
		
		if (enemy[enemy_id].flag && enemy[enemy_id].emitter_state == EMITTER_CLEAR) { 
			for (int id = 0; id < BULLET_MAX; id++) {
				i = bullet_id_list[id];
				if (i < 0) continue;
				if (bullet[i].flag) {
					bullet[i].flag = false;
					bullet[i].Free();
					bullet_id_list[id] = -1;
				}
			}
			enemy[enemy_id].flag = false;
			this->flag = false;//销毁自身
			return;
		}

		
		if (!enemy[enemy_id].flag)	//所有者不存在，等待弹幕消失，然后销毁
			state = EMITTER_WAIT;
		else
			Emitter_barrage[enemy[enemy_id].blknd](this);

		int bullet_num = 0;
		for (int id = 0; id < BULLET_MAX; id++) {
			i = bullet_id_list[id];
			if (i < 0) continue;
			if (bullet[i].flag) {
				bullet_num++;
				bullet[i].x += cos(bullet[i].angle) * bullet[i].spd;
				bullet[i].y += sin(bullet[i].angle) * bullet[i].spd;
				//printf("cnt %d bullet x %lf y %lf\n",cnt, bullet[i].x, bullet[i].y);
				bullet[i].frame++;
				if (bullet[i].x< (double)FX - 50 || bullet[i].x>(double)FMX + 50 || bullet[i].y< (double)FY - 50 || bullet[i].y>(double)FMY + 50) {//如果跑到画面外面的话
					if (bullet[i].till < bullet[i].frame) {//且比最低程度不会销毁的时间还要很长
						bullet[i].flag = false;//销毁之
						bullet[i].Free();
						bullet_id_list[id] = -1;
						//printf("bullet remove enemy_id:%d bullet_id:%d\n", enemy_id,i);
					}
				}
			}
		}
		if(bullet_num == 0 && state == EMITTER_WAIT)
			this->flag = false;//销毁自身

		//printf("bullet num :%d\n", k);
		//查询当前显示中的子弹的熟练是否至少还有一个

		/*if (!enemy[enemy_id].flag) {
			flag = -1;//終了
			enemy[enemy_id].flag = false;
			//printf("cnt %d emitter remove enemy_id:%d\n", cnt,enemy_id);
		}*/

		frame++;

	}
}