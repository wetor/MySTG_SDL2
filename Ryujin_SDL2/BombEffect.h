#ifndef __BOMBEFFECT_H__
#define __BOMBEFFECT_H__
#include "Effect.h"
namespace NspEffect {
	class BombEffect :
		public Effect
	{
	public:
		BombEffect();
		~BombEffect();
		void Init(effect_t* data);
		void Render();
		void Update();
		bool isExist() { return flag; };
	public:
		bool flag;
		int col, knd, eff, brt;
	};

}
#endif
