#pragma once
#include "Unit.h"
#include "Effect.h"
namespace NspBoss {
	class Boss : 
		public Unit
	{
	public:
		Boss();
		void Init(boss_t _boss_data);
		void Enter(int num);
		void Render();
		void Update();
		bool isExist() { return flag; };
		void AddEmitter(int emitter_id);
		void DestroyEmitter(int emitter_id);
		void Death();
		int get_knd() {
			return sc_knd[sc_index];
		}
		int get_enter(int index) {
			if (index < sc_num)
				return sc_enter[index];
			return -1;
		}
		int get_bg() {
			return sc_bg[sc_index];
		}
		int move_boss_pos(float x1, float y1, float x2, float y2, float dist, int t);
		void input_phy_pos(float x, float y, int t);
	private:
		void input_phy(int t);
		
		
	public:
		bool flag = false;
		bool emitter_id[EMITTER_MAX];
		EMITTER_STATE emitter_state[EMITTER_MAX];
		phy_t phy;
		BOSS_STATE state;
		SDL_Surface* hp_surface;
		SDL_Texture* hp_texture;

		NspEffect::BossEffect *bg_effect;
		float dx, dy;
		float base_angle[2];
		int frame_shot;
		int wtime, endtime, hagoromo, graph_flag;
		int hp, hp_max;
		int sc_index;
		int sc_num; //弹幕数
		int* sc_knd; //弹幕类型
		int* sc_hp; //hp
		int* sc_bg; //背景类型
		int* sc_enter; //出现时间
	};

}