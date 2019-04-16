#pragma once



#include "Player.h"
#include "Enemy.h"

#include "Emitter.h"
#include "Bullet.h"

#include "struct.h"
#include <list>
#include <iostream>
using namespace std;
extern  Player *player;
//extern  list<Enemy*> enemy;
extern  Enemy* enemy;

extern  Emitter* emitter;
extern	Bullet* bullet;


extern  list<enemy_order_t> enemy_order;
extern  bool WindowInit();
extern  void ResourcesInit();

extern  void PlayerInit();
extern  void EnemyInit();

extern  void EnemyEnter();
extern  void EnemyUpdate();
extern  void EnemyDraw();


extern	void EmitterInit();
extern	int EmitterEnter(int enemy_id);
extern	void EmitterUpdate();

extern	int BulletEnter(bullet_t * data);
extern	void BulletUpdate();
extern	void BulletDraw();


extern	void FpsShow(int x, int y);
extern	void FpsWait();
extern	void FpsWaitOnly();
