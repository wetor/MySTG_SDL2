/*
子弹管理者
管理自机、敌人和BOSS的子弹更新、显示等

独立一个线程，或用多个线程来优化效率

 */

#include "pch.h"
#include "define.h"
#include "global.h"
#include "Manager.h"

Emitter* emitter = NULL;
Bullet* bullet = NULL;

void EmitterInit() {
	emitter = new Emitter[EMITTER_MAX];
	bullet = new Bullet[BULLET_MAX];
}
inline int search_emitter() {
	for (int i = 0; i < EMITTER_MAX; i++) {
		if (!emitter[i].isExist())
			return i;
	}
	return -1;
}

int EmitterEnter(int enemy_id) {
	
	int k = search_emitter();
	if (k != -1)
		emitter[k].Init(enemy_id);
	return k;
}

void EmitterUpdate() {
	for (int i = 0; i < EMITTER_MAX; i++) {
		if (emitter[i].isExist()) {
			emitter[i].Update();
		}
	}
}

inline int search_bullet() {
	for (int i = 0; i < BULLET_MAX; i++) {
		if (!bullet[i].isExist())
			return i;
	}
	return -1;
}

int BulletEnter(bullet_t * data) {

	int k = search_bullet();
	if (k != -1)
		bullet[k].Init(data);
	return k;
}

void BulletUpdate() {
	for (int i = 0; i < BULLET_MAX; i++) {
		if (bullet[i].isExist()) {
			bullet[i].Update();
		}
	}
}

void BulletDraw() {
	for (int i = 0; i < BULLET_MAX; i++) {
		if (bullet[i].isExist()) {
			bullet[i].Draw();
		}
	}
}