#ifndef __COLLIDER_H__
#define __COLLIDER_H__
#include "Manager.h"
class Collider
{
public:
	static bool Judge(NspBullet::Bullet *bullet,Unit* unit);
	static void PlayerShotEnemy();
	static void PlayerBombEnemy();
	static void EnemyShotPlayer();
};

#endif