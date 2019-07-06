#include "pch.h"
#include "Emitter.h"
#include "Manager.h"


namespace NspEmitter {

	double rang(double ang) {
		return (-ang + ang * 2 * (rand() % 10000) / 10000.0);
	}

	double shotatan2(int enemy_id) {

		return atan2(player->y - enemy[enemy_id].y, player->x - enemy[enemy_id].x);
	}

	/*double rang(double max) {
		return (rand() % (int)(max * 1000)) / 1000.0;
	}*/
	//只发射一发，向自机直线移动
	void emitter_bullet_H000(Emitter* _this) {
		int enemy_id = _this->enemy_id;
		int bullet_id = 0;
		int t = _this->frame;
		//for (int z = 0; z < 3; z++)
		if (t == 10) {

			bullet_t temp;

			temp.knd = enemy[enemy_id].blknd2;
			temp.angle = shotatan2(enemy_id);
			temp.flag = 1;
			temp.x = enemy[enemy_id].x;
			temp.y = enemy[enemy_id].y;
			temp.col = enemy[enemy_id].col;
			temp.cnt = 0;
			temp.spd = 3;

			bullet_id = NspBullet::BulletEnter(&temp);
			_this->AddBulletID(bullet_id);
			Sound::PlayMusic(0);
			//_this->bullet_id.push_back(bullet_id);
		}



	}
	//100次计数中发射10发，朝着自机直线发射（一般是自机狙）
	void emitter_bullet_H001(Emitter* _this) {
		int enemy_id = _this->enemy_id;
		int bullet_id = 0;
		int t = _this->frame;
		if (t >= 0 && t < 100 && t % 10 == 0) { //100次计数每10次计数1次
			bullet_t temp;
			temp.knd = enemy[enemy_id].blknd2;//子弹的登录
			temp.angle = shotatan2(enemy_id);//角度
			temp.flag = 1;//flag
			temp.x = enemy[enemy_id].x;//坐标
			temp.y = enemy[enemy_id].y;
			temp.col = enemy[enemy_id].col;//颜色
			temp.cnt = 0;//计数器
			temp.spd = 3;//速度

			bullet_id = NspBullet::BulletEnter(&temp);
			_this->AddBulletID(bullet_id);
			//_this->bullet_id.push_back(bullet_id);
			Sound::PlayMusic(0);
		}
	}
	//100次计数中发射10发，向着自机直线发射（记忆角度）
	void emitter_bullet_H002(Emitter* _this) {
		int enemy_id = _this->enemy_id;
		int bullet_id = 0;
		int t = _this->frame;
		if (t >= 0 && t < 100 && t % 10 == 0) {
			if (t == 0)
				_this->base_angle[0] = shotatan2(enemy_id);
			bullet_t temp;
			temp.knd = enemy[enemy_id].blknd2;
			temp.angle = _this->base_angle[0];
			temp.flag = 1;
			temp.x = enemy[enemy_id].x;
			temp.y = enemy[enemy_id].y;
			temp.col = enemy[enemy_id].col;
			temp.cnt = 0;
			temp.spd = 3;
			//se_flag[0] = 1;
			bullet_id = NspBullet::BulletEnter(&temp);
			_this->AddBulletID(bullet_id);
			//_this->bullet_id.push_back(bullet_id);
			Sound::PlayMusic(0);
		}
	}

	//100次计数中10发，向着自机速度变化地直线发射
	void emitter_bullet_H003(Emitter* _this) {
		int enemy_id = _this->enemy_id;
		int bullet_id = 0;
		int t = _this->frame;
		if (t >= 0 && t < 100 && t % 10 == 0) {
			bullet_t temp;
			temp.knd = enemy[enemy_id].blknd2;
			temp.angle = shotatan2(enemy_id);
			temp.flag = 1;
			temp.x = enemy[enemy_id].x;
			temp.y = enemy[enemy_id].y;
			temp.col = enemy[enemy_id].col;
			temp.cnt = 0;
			temp.spd = 1 + 5.0 / 100 * t;
			//se_flag[0] = 1;
			bullet_id = NspBullet::BulletEnter(&temp);
			_this->AddBulletID(bullet_id);
			//_this->bullet_id.push_back(bullet_id);
			Sound::PlayMusic(0);
		}
	}
	//0.5秒一次地圆形发射
	void emitter_bullet_H004(Emitter* _this) {
		int enemy_id = _this->enemy_id;
		int bullet_id = 0;
		int t = _this->frame;
		if (t >= 0 && t < 120 && t % 20 == 0) {
			double angle = shotatan2(enemy_id);
			for (int i = 0; i < 20; i++) {
				bullet_t temp;

				temp.knd = enemy[enemy_id].blknd2;
				temp.angle = angle + PI2 / 20 * i;
				temp.flag = 1;
				temp.x = enemy[enemy_id].x;
				temp.y = enemy[enemy_id].y;
				temp.col = enemy[enemy_id].col;
				temp.cnt = 0;
				temp.spd = 4;

				bullet_id = NspBullet::BulletEnter(&temp);
				_this->AddBulletID(bullet_id);
				//_this->bullet_id.push_back(bullet_id);
				Sound::PlayMusic(0);
			}
		}
	}
	//散射
	void emitter_bullet_H005(Emitter* _this) {
		int enemy_id = _this->enemy_id;
		int bullet_id = 0;
		int t = _this->frame;
		if (t >= 0 && t < 120 && t % 2 == 0) {
			bullet_t temp;
			temp.knd = enemy[enemy_id].blknd2;
			temp.angle = shotatan2(enemy_id) + rang(PI / 4);
			temp.flag = 1;
			temp.x = enemy[enemy_id].x;
			temp.y = enemy[enemy_id].y;
			temp.col = enemy[enemy_id].col;
			temp.cnt = 0;
			temp.spd = 3 + rang(1.5);
			//se_flag[0] = 1;
			bullet_id = NspBullet::BulletEnter(&temp);
			_this->AddBulletID(bullet_id);
			//_this->bullet_id.push_back(bullet_id);
			Sound::PlayMusic(0);
		}
	}

	//散射（减速）
	void emitter_bullet_H006(Emitter* _this) {
		int enemy_id = _this->enemy_id;
		int bullet_id = 0;
		int t = _this->frame;
		if (t >= 0 && t < 120 && t % 2 == 0) {
			bullet_t temp;
			temp.knd = enemy[enemy_id].blknd2;
			temp.angle = shotatan2(enemy_id) + rang(PI / 4);
			temp.flag = 1;
			temp.x = enemy[enemy_id].x;
			temp.y = enemy[enemy_id].y;
			temp.col = enemy[enemy_id].col;
			temp.cnt = 0;
			temp.spd = 4 + rang(2);
			//se_flag[0] = 1;
			bullet_id = NspBullet::BulletEnter(&temp);
			_this->AddBulletID(bullet_id);
			//_this->bullet_id.push_back(bullet_id);
			Sound::PlayMusic(0);
		}
		for (int id = 0; id < SHOT_BULLET_MAX; id++) {
			if (bullet[_this->bullet_id_list[id]].spd > 1.5)//如果速度大于1.5的话
				bullet[_this->bullet_id_list[id]].spd -= 0.04;//减速

		}
		/*
		for (auto id = _this->bullet_id.begin(); id != _this->bullet_id.end();) {//所有子弹的循环
			if (bullet[*id].spd > 1.5)//如果速度大于1.5的话
				bullet[*id].spd -= 0.04;//减速
		}*/

	}
	//妖梦弹幕
	void emitter_bullet_H007(Emitter* _this) {
		int enemy_id = _this->enemy_id;
		int bullet_id = 0;
		int t = _this->frame;
		if (t >= 0 && t <= 150 && t % 10 == 0) {
			for (int i = 0; i < 20; i++) {
				bullet_t temp;
				temp.knd = 7;
				temp.angle = PI2 / 20 * i;
				temp.flag = 1;
				temp.x = enemy[enemy_id].x + cos(PI / 2 + PI / 150 * t) * 100;
				temp.y = enemy[enemy_id].y + sin(PI / 2 + PI / 150 * t) * 100;
				temp.col = 2;
				temp.cnt = 0;
				temp.spd = 1.2;
				bullet_id = NspBullet::BulletEnter(&temp);
				_this->AddBulletID(bullet_id);
			}
			for (int i = 0; i < 20; i++) {
				bullet_t temp;
				temp.knd = 7;
				temp.angle = PI2 / 20 * i;
				temp.flag = 1;
				temp.x = enemy[enemy_id].x + cos(PI / 2 - PI / 150 * t) * 100;
				temp.y = enemy[enemy_id].y + sin(PI / 2 - PI / 150 * t) * 100;
				temp.col = 4;
				temp.cnt = 0;
				temp.spd = 1.2;
				bullet_id = NspBullet::BulletEnter(&temp);
				_this->AddBulletID(bullet_id);
				//se_flag[0] = 1;
				Sound::PlayMusic(0);
				
			}
		}
	}
	//诹访子大人
	void emitter_bullet_H008(Emitter* _this) {
		int enemy_id = _this->enemy_id;
		int bullet_id = 0;
		int t = _this->frame;
		if (t >= 0 && t < 1200 && t % 90 == 0) {
			double angle = rang(PI);
			for (int j = 0; j < 2; j++) {//中途的时候就分裂为两部分
				for (int i = 0; i < 60; i++) {//一次60个
					bullet_t temp;
					temp.knd = 8;
					temp.angle = angle + PI2 / 60 * i;//60个圆
					temp.flag = 1;
					temp.x = enemy[enemy_id].x;
					temp.y = enemy[enemy_id].y;
					temp.col = 4;
					temp.cnt = 0;
					temp.state = j;//状态。0或者是1表示不同旋转。
					temp.spd = 2;
					bullet_id = NspBullet::BulletEnter(&temp);
					_this->AddBulletID(bullet_id);
				}
			}
			//se_flag[0] = 1;//播放发射音效
			Sound::PlayMusic(0);
		}

		for (int id = 0; id < BULLET_MAX; id++) {
			if (bullet[_this->bullet_id_list[id]].isExist()) {//如果有登录了的子弹
				int i = _this->bullet_id_list[id];
				int state = bullet[i].state;
				int cnt = bullet[i].frame;
				if (30 < cnt && cnt < 120) {//如果是30~120次计数
					bullet[i].spd -= 1.2 / 90.0;//90次计数总共减去1.2
					bullet[i].angle += (PI / 2) / 90.0 * (state ? -1 : 1);//90次计数总共倾斜90°
				}
			}
		}

	}



}