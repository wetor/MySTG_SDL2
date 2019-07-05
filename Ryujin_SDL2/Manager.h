#pragma once
#include "Bullet.h"
#include "Emitter.h"
#include "Enemy.h"
#include "Player.h"
#include "Sound.h"
#include "struct.h"
#include <iostream>
#include <list>
using namespace std;
extern  NspPlayer::Player *player;
//extern  list<Enemy*> enemy;
extern  NspEnemy::Enemy* enemy;

extern  NspEmitter::Emitter* emitter;
extern	NspBullet::Bullet* bullet;
extern	NspBullet::Bullet* player_bullet;

extern  list<enemy_order_t> enemy_order;
extern  bool WindowInit();
extern  void ResourcesInit();

extern	void NumberShow(int x, int y, int num);



namespace NspPlayer {
	extern  void PlayerInit();
	extern  void PlayerUpdate();
	extern  void PlayerDraw();
}

namespace NspEnemy {
	extern  void EnemyInit();
	extern  void EnemyEnter();
	extern  void EnemyUpdate();
	extern  void EnemyDraw();
#ifdef DEBUG
	extern  void EnemyNumberShow(int x, int y);
#endif
}
namespace NspEmitter {
	extern	void EmitterInit();
	extern	int	 EmitterEnter(int enemy_id);
	extern	void EmitterUpdate();
#ifdef DEBUG
	extern  void EmitterNumberShow(int x, int y);
#endif
}
namespace NspBullet {
	extern	int  BulletEnter(bullet_t* data);
	extern	void BulletUpdate();
	extern	void BulletDraw();
	extern	int  PlayerBulletEnter(player_bullet_t* data);
	extern	void PlayerBulletUpdate();
	extern	void PlayerBulletDraw();
#ifdef DEBUG
	extern  void BulletNumberShow(int x, int y);
#endif
}
namespace NspWindow {
	extern	void FpsShow(int x, int y);
	extern	void FpsWait();
}

