#include "pch.h"
#include "Effect.h"
#include "Manager.h"


namespace NspEffect {

	DeathBombEffect::DeathBombEffect()
	{
		memset(effect_id, -1, sizeof(int) * 10);
	}
	void DeathBombEffect::Init()
	{
		for (int i = 0; i < 10; i++) {
			effect_t temp;
			temp.img = "eft0";
			temp.wait = i * 2;//等待帧数
			temp.brt = 255;//将亮度变为最大值
			temp.ang = rang(PI);//随机角度
			temp.col = rand()%5;//设置颜色
			temp.eff = 2;// 1是发光效果。这里设置为光效果。
			temp.knd = 4;//决死特效
			temp.r = 0;
			temp.spd = 0;
			temp.x = player->x;//设置坐标
			temp.y = player->y;
			effect_id[i] = EffectEnter(&temp);
		}
	}
	void DeathBombEffect::Update()
	{
		// 交给Effect内部处理
	}
}