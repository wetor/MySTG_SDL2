#pragma once



#include "Player.h"
#include "Enemy.h"

#include "Emitter.h"
#include "Bullet.h"

#include "struct.h"
#include <list>
#include <iostream>
using namespace std;
extern  NspPlayer::Player *player;
//extern  list<Enemy*> enemy;
extern  NspEnemy::Enemy* enemy;

extern  NspEmitter::Emitter* emitter;
extern	NspBullet::Bullet* bullet;


extern  list<enemy_order_t> enemy_order;
extern  bool WindowInit();
extern  void ResourcesInit();

extern	void NumberShow(int x, int y, int num);



namespace NspPlayer {
	extern  void PlayerInit();
}

namespace NspEnemy {
	extern  void EnemyInit();
	extern  void EnemyEnter();
	extern  void EnemyUpdate();
	extern  void EnemyDraw();
}
namespace NspEmitter {
	extern	void EmitterInit();
	extern	int EmitterEnter(int enemy_id);
	extern	void EmitterUpdate();
}
namespace NspBullet {
	extern	int BulletEnter(bullet_t* data);
	extern	void BulletUpdate();
	extern	void BulletDraw();

}

namespace NspFps {

	extern	void FpsShow(int x, int y);
	extern	void FpsWait();
}

