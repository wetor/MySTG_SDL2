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


void(*Emitter_barrage[EMITTER_BARRAGE_MAX])(Emitter *) = {
		emitter_bullet_H000,emitter_bullet_H001,emitter_bullet_H002,emitter_bullet_H003,emitter_bullet_H004,emitter_bullet_H005,emitter_bullet_H006
};

Emitter::Emitter()
{
}


Emitter::~Emitter()
{
}
void Emitter::Init(int enemy_id) {
	
	this->enemy_id = enemy_id;
	this->x = enemy[enemy_id].x;
	this->y = enemy[enemy_id].y;
	flag = 1;
	frame = 0;
}

void Emitter::Update() {
	
	Emitter_barrage[enemy[enemy_id].blknd](this);
	int i, k;
	if (!enemy[enemy_id].flag)//如果敌人被打倒的话
		flag = 2;//将之前登录的射击的flag设置为无效
	for (auto id = bullet_id.begin(); id != bullet_id.end();) {
		i = *id;
		k = 0;
		if (bullet[i].flag) {
			bullet[i].x += cos(bullet[i].angle)*bullet[i].spd;
			bullet[i].y += sin(bullet[i].angle)*bullet[i].spd;
			//printf("cnt %d bullet x %lf y %lf\n",cnt, bullet[i].x, bullet[i].y);
			bullet[i].frame++;
			if (bullet[i].x<FX - 50 || bullet[i].x>FMX + 50 || bullet[i].y<FY - 50 || bullet[i].y>FMY + 50) {//如果跑到画面外面的话
				if (bullet[i].till < bullet[i].frame) {//且比最低程度不会销毁的时间还要很长
					bullet[i].flag = false;//销毁之
					bullet[i].Free();
					id = bullet_id.erase(id);
					k = 1;
					//printf("bullet remove enemy_id:%d bullet_id:%d\n", enemy_id,i);
				}
			}
		}
		if(k==0)
			id++;
	}
	//查询当前显示中的子弹的熟练是否至少还有一个
	
	/*if (!enemy[enemy_id].flag) {
		flag = -1;//終了
		enemy[enemy_id].flag = false;
		//printf("cnt %d emitter remove enemy_id:%d\n", cnt,enemy_id);
	}*/

	frame++;

}