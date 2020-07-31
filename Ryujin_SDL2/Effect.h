#pragma once
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


	class DeathEffect // 敌人死亡特效
	{
	public:
		DeathEffect();
		DeathEffect(NspEnemy::Enemy* _enemy);
		void Init(NspEnemy::Enemy* _enemy);
		void Update();
	public:
		int effect_id[5];
	};

	class BombEffect //Bomb特效
	{
	public:
		BombEffect();
		void Bomb();
		void Update();
	public:
		int effect_id[3 + 4];//3个界面效果，4个动态效果
		bom_t bom;
	};

	class DeathBombEffect //决死特效
	{
	public:
		DeathBombEffect();
		void Init();
		void Update();
	public:
		int effect_id[10];
	};

	class BossEffect //Boss特效
	{
	public:
		BossEffect();
		void Init();
		void Update();
		void Clear();
	public:
		int effect_id[5];
		bool flag = false;
	};

}
