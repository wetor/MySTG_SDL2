#pragma once
#include "Manager.h"
class Collider
{
public:
	static bool Judge(NspBullet::Bullet *bullet,Unit* unit);
	static void PlayerShotEnemy();
};

