/*
碰撞判断
*/
#include "pch.h"
#include "Collider.h"
bool Collider::Judge(NspBullet::Bullet* bullet, Unit* unit) {
	int j;
	if (bullet->frame > 0) { //如果射击的子弹的轨道至少计算过1次
		float x = bullet->x - unit->x; //敌人和自机射击的子弹的距离
		float y = bullet->y - unit->y;
		//防止溢出

		/*if (bullet.knd >= bullet_RANGE_MAX || unit.knd >= unit_RANGE_MAX)
			printfDx("out_judge_bullet溢出");*/

		//敌人的碰撞判定和自机射击的子弹的碰撞判定的合计范围
		float r = bullet->range + unit->range;
		//如果有必要计算中间的话
		if (bullet->spd > r) {
			//保存1帧之前的位置
			float pre_x = bullet->x + cos(bullet->angle + PI) * bullet->spd;
			float pre_y = bullet->y + sin(bullet->angle + PI) * bullet->spd;
			float px, py;
			for (j = 0; j < bullet->spd / r; j++) {//前进部分÷碰撞判定部分次循环
				px = pre_x - unit->x;
				py = pre_y - unit->y;
				if (px * px + py * py < r * r)
					return true;
				pre_x += cos(bullet->angle) * r;
				pre_y += sin(bullet->angle) * r;
			}
		}
		if (x * x + y * y < r * r)//如果在碰撞判定范围内
			return true;//碰撞
	}
	return false;


}
void Collider::PlayerShotEnemy() {
	for (int i = 0; i < PLAYER_BULLET_MAX; i++) {
		if (player_bullet[i].isExist()) {
			for (int e = 0; e < ENEMY_MAX; e++) {
				if (enemy[e].isExist()) {
					if (Judge(&player_bullet[i], &enemy[e])) {
						//LogA("dis %d %d",i,e);
						player_bullet[i].flag = false;
						player_bullet[i].Free();
						enemy[e].hp -= player_bullet[i].power;
						Sound::PlayMusic(2);
						if (enemy[e].Death()) {
							NspEffect::DeathEnter(&enemy[e]);
							enemy[e].Destroy(false);//弹幕停止发射，不清空
							Sound::PlayMusic(3);
						}
						
					}
				}
			}
		}
	}
}
void Collider::PlayerBombEnemy() {
	if (player->bomb->bom.flag != 1) return;
	for (int e = 0; e < ENEMY_MAX; e++) {
		if (enemy[e].isExist()) {
			enemy[e].hp -= player->power / 20;
			//Sound::PlayMusic(2);
			if (enemy[e].Death()) {
				NspEffect::DeathEnter(&enemy[e]);
				enemy[e].Destroy(false);//弹幕停止发射，清空
				Sound::PlayMusic(3);
			}
		}
	}
}
void Collider::EnemyShotPlayer() {
	for (int i = 0; i < BULLET_MAX; i++) {
		if (bullet[i].isExist()) {
			
			if (Judge(&bullet[i], player)) {
				bullet[i].flag = false;
				bullet[i].Free();
				if (player->state == PLAYER_DEFAULT) {
					//状态为一般状态，且不是无敌状态下
					player->state = PLAYER_DEATH;
					player->frame = 0;
					Sound::PlayMusic(4);//击毁声
					return;
				}
			}
		}
	}
}