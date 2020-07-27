#pragma once
#include "Bullet.h"
#include "Effect.h"
#include "Emitter.h"
#include "Enemy.h"
#include "Boss.h"
#include "Environment.h"
#include "Player.h"
#include "Sound.h"
#include "struct.h"
#include "Tools.h"
#include <iostream>
#include <list>
#include <memory>
using namespace std;
//extern  NspPlayer::Player *player;
//extern  NspEnemy::Enemy* enemy;

extern	NspPlayer::Player* player;

extern	NspBoss::Boss* boss;

extern	NspEnvironment::Environment* env;

extern  NspEnemy::Enemy enemy[];

extern  NspEmitter::Emitter emitter[];
extern	NspBullet::Bullet bullet[];
extern	NspBullet::Bullet player_bullet[];
extern	NspEffect::Effect effect[];

extern  list<enemy_order_t> enemy_order;


extern  bool WindowInit();
extern  void ResourcesInit();



namespace NspEnvironment {
	extern  void EnvInit();
	extern  void EnvUpdate();
	extern  void EnvRender();
}

namespace NspPlayer {
	extern  void PlayerInit();
	extern  void PlayerUpdate();
	extern  void PlayerRender();
}

namespace NspBoss {
	extern  void BossInit();
	extern	void BossEnter();
	extern  void BossUpdate();
	extern  void BossRender();
}

namespace NspEnemy {
	extern  void EnemyInit();
	extern  void EnemyEnter();
	extern  void EnemyUpdate();
	extern  void EnemyRender();
	extern	void EnemyClear();
#ifdef DEBUG
	extern  void EnemyNumberShow(int x, int y);
#endif
}
namespace NspEmitter {
	extern	void EmitterInit();
	extern	int	 EmitterEnter(int enemy_id, bool is_boss=false);
	extern	void EmitterClear(bool clear_bullet = false);
	extern	void EmitterUpdate();
#ifdef DEBUG
	extern  void EmitterNumberShow(int x, int y);
#endif
}
namespace NspBullet {
	extern	int  BulletEnter(bullet_t* data);
	extern	void BulletUpdate();
	extern	void BulletRender();
	extern	void BulletClear();
	extern	int  PlayerBulletEnter(player_bullet_t* data);
	extern	void PlayerBulletUpdate();
	extern	void PlayerBulletRender();
#ifdef DEBUG
	extern  void BulletNumberShow(int x, int y);
#endif
}
namespace NspWindow {
	extern	void FpsShow(int x, int y);
	extern	void FpsWait();
}

namespace NspEffect {
	extern	void EffectInit();
	extern	void DeathEnter(NspEnemy::Enemy* _enemy);
	extern	void EffectUpdate();
	extern	void EffectRender();
}

