#pragma once
#include "Unit.h"
namespace NspBoss {
	class Boss : 
		public Unit
	{
	public:
		Boss();
		void Init(int num);
		void Render();
		void Update();
		bool isExist() { return flag; };
		void AddEmitter(int emitter_id);
		void DestroyEmitter(int emitter_id);
	private:
		void input_phy(int t);
	public:
		bool flag = false;
		int emitter_id[EMITTER_MAX];
		EMITTER_STATE emitter_state[EMITTER_MAX];
		int appear_count;
		phy_t phy;
		BOSS_STATE state;
		int frame_shot;
		int wtime, endtime, hagoromo, graph_flag;
		int hp, hp_max;
		int knd;
	};

}