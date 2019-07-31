/*
环境相关
包括背景、不可判断单位的绘制、更新，不包括UI

*/
#ifndef __ENVIRONMENT_H__
#define __ENVIRONMENT_H__
#include "Unit.h"

namespace NspEnvironment {

	class Environment :
		public Unit
	{
	public:
		Environment() {};
		void Init();
		void Update();
		void Render();


	};

}
#endif