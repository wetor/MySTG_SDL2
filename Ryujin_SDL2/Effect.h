#ifndef __EFFECT_H__
#define __EFFECT_H__
#include "Unit.h"
#include "Enemy.h"

namespace NspEffect {
	class Effect :
		public Unit
	{
	public:
		Effect();
		~Effect();
		void Init(effect_t* data);
		void Render();
		void Update();
		bool isExist() { return flag; };
	public:
		bool flag;
		int col, knd, eff;
		float spd, move_angle, brt;
	};

	extern float rang(double ang);
	extern int EffectEnter(effect_t* data);


	class DeathEffect
	{
	public:
		DeathEffect();
		DeathEffect(NspEnemy::Enemy* _enemy);
		void Init(NspEnemy::Enemy* _enemy);
		void Update();
	public:
		int effect_id[5];
	};

	class BombEffect
	{
	public:
		BombEffect();
		void Bomb();
		void Update();
	public:
		int effect_id[3 + 4];//3个界面效果，4个动态效果
		bom_t bom;
	};
}
#endif