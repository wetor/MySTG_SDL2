#include "pch.h"
#include "Effect.h"


namespace NspEffect {

	DeathEffect::DeathEffect()
	{
		memset(effect_id, -1, sizeof(int) * 5);
	}
	DeathEffect::DeathEffect(NspEnemy::Enemy* _enemy)
	{
		this->Init(_enemy);
	}
	void DeathEffect::Init(NspEnemy::Enemy* _enemy)
	{
		for (int i = 0; i < 5; i++) {
			effect_t temp;
			temp.img = "eft0";
			temp.wait = i * 2;//等待帧数
			temp.brt = 255;//将亮度变为最大值
			temp.ang = rang(PI);//随机角度
			temp.col = _enemy->back_col;//设置颜色
			temp.eff = 1;// 1是发光效果。这里设置为光效果。
			temp.knd = 0;//效果的种类是0号（消灭特效的knd一定是0）
			temp.r = 0.5;
			temp.x = _enemy->x;//设置坐标
			temp.y = _enemy->y;
			effect_id[i] = EffectEnter(&temp);
		}
	}
	void DeathEffect::Update()
	{
	}
}