#pragma once
#include "Unit.h"
namespace NspEffect {
	class Effect :
		public Unit
	{
	public:
		Effect();
		~Effect();
		void Init(effect_t* data);
		void Draw();
		void Update();
		bool isExist() { return flag; };
	public:
		bool flag;
		int col, knd, eff, brt;
	};

}