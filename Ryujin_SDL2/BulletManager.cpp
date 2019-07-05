/*
子弹管理者
管理自机、敌人和BOSS的子弹更新、显示等

独立一个线程，或用多个线程来优化效率

 */

#include "pch.h"
#include "define.h"
#include "global.h"
#include "Manager.h"


NspBullet::Bullet* bullet = NULL;
NspBullet::Bullet* player_bullet = NULL;

namespace NspBullet {

	inline int search_bullet() {
		for (int i = 0; i < BULLET_MAX; i++) {
			if (!bullet[i].isExist())
				return i;
		}
		return -1;
	}

	int BulletEnter(bullet_t* data) {

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
#ifdef DEBUG
	void BulletNumberShow(int x, int y) {
		int num = 0;
		for (int i = 0; i < BULLET_MAX; i++) {
			if (bullet[i].isExist()) {
				num++;
			}
		}
		NumberShow(x,y, num);

	}
#endif
	void BulletDraw() {
		for (int i = 0; i < BULLET_MAX; i++) {
			if (bullet[i].isExist()) {
				bullet[i].Draw();
			}
		}
	}


	//----------------------------------
	inline int search_player_bullet() {
		for (int i = 0; i < PLAYER_BULLET_MAX; i++) {
			if (!player_bullet[i].isExist())
				return i;
		}
		return -1;
	}

	int PlayerBulletEnter(player_bullet_t* data) {

		int k = search_player_bullet();
		if (k != -1)
			player_bullet[k].Init(data);
		return k;
	}

	void PlayerBulletUpdate() {
		for (int i = 0; i < PLAYER_BULLET_MAX; i++) {
			if (player_bullet[i].isExist()) {
				player_bullet[i].Update();
			}
		}
	}

	void PlayerBulletDraw() {
		for (int i = 0; i < PLAYER_BULLET_MAX; i++) {
			if (player_bullet[i].isExist()) {
				player_bullet[i].Draw();
			}
		}
	}
}