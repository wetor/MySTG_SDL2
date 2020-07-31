#pragma once
#include "define.h"
#include "struct.h"
#include <deque>
namespace NspEmitter {
	class Emitter
	{
	public:
		Emitter();
		bool isExist() { return flag; };
		int AddBulletID(int id);
		void Init(int enemy_id, int emitter_id, bool is_boss = false);
		void Update();
		void Clear();
	public:
		bool flag = false;
		int id;
		bool is_boss = false; // 是否为boos
		EMITTER_STATE state;
		//种类、计数器、发射的敌人的编号
		int  enemy_id, knd, frame;
		//基本角度、基本速度
		float x, y, base_angle[1], base_spd[1];
		int bullet_num;
		bool bullet_id[BULLET_MAX];

	};

	float rang(float ang);
	float shotatan2(int enemy_id);
	float bossatan2();
	void emitter_bullet_H000(Emitter* _this);
	void emitter_bullet_H001(Emitter* _this);
	void emitter_bullet_H002(Emitter* _this);
	void emitter_bullet_H003(Emitter* _this);
	void emitter_bullet_H004(Emitter* _this);
	void emitter_bullet_H005(Emitter* _this);
	void emitter_bullet_H006(Emitter* _this);
	void emitter_bullet_H007(Emitter* _this);
	void emitter_bullet_H008(Emitter* _this);


	void boss_shot_bulletH000(Emitter* _this);
	void boss_shot_bulletH001(Emitter* _this);
	void boss_shot_bulletH002(Emitter* _this);
}
