#pragma once
#include "struct.h"
#include "define.h"
#include "Unit.h"
namespace NspBullet {
	class Bullet :public Unit
	{
	public:
		Bullet();
		~Bullet();
		bool isExist() { return flag; };
		void Init(bullet_t* data);
		void Update();
		void Free();
	public:
		bool flag;
		//种类、计数器、颜色、状态、保证不消失的最短时间、效果的种类
		int  knd, col, state, till, eff;
		//坐标、速度、基本角度、瞬间记忆速度
		double  spd, base_angle[1], rem_spd[1];
	};
}
