#include "pch.h"
#include "define.h"
#include "global.h"
#include "Manager.h"

NspEffect::Effect effect[EFFECT_MAX];
//NspEffect::Effect* effect = NULL;
namespace NspEffect {
	float rang(double ang) {
		return (float)(-ang + ang * 2 * (rand() % 10000) / 10000.0);
	}
	inline int search_effect() {
		for (int i = 0; i < EFFECT_MAX; i++) {
			if (!effect[i].isExist()) {
				return i;
			}
		}
		return -1;
	}
	int EffectEnter(effect_t* data) {

		int k = search_effect();
		if (k != -1)
			effect[k].Init(data);
		//LogA("Effect enter %d", k);
		return k;
	}
	void EffectInit() {
		//effect = new Effect[EFFECT_MAX];
	}

	void DeathEnter(NspEnemy::Enemy* _enemy) {
		for (int i = 0; i < 5; i++) {
			effect_t temp;
			temp.wait = i * 2;//等待帧数
			temp.brt = 255;//将亮度变为最大值
			temp.ang = rang(PI);//随机角度
			temp.col = _enemy->back_col;//设置颜色
			temp.eff = 1;// 1是发光效果。这里设置为光效果。
			temp.knd = 0;//效果的种类是0号（消灭特效的knd一定是0）
			temp.r = 0.5;
			temp.x = _enemy->x;//设置坐标
			temp.y = _enemy->y;
			EffectEnter(&temp);
		}
	}
	void EffectUpdate() {
		for (int i = 0; i < EFFECT_MAX; i++) {
			if (effect[i].isExist()) {
				effect[i].Update();
			}
		}
	}
	void EffectRender() {
		for (int i = 0; i < EFFECT_MAX; i++) {
			if (effect[i].isExist()) {
				effect[i].Render();
			}
		}
	}
}
