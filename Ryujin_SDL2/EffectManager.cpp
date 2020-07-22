#include "pch.h"
#include "define.h"
#include "global.h"
#include "Manager.h"

NspEffect::Effect effect[EFFECT_MAX];

bom_t bom;
dn_t dn;
//NspEffect::Effect* effect = NULL;
namespace NspEffect {

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
		new DeathEffect(_enemy);
	}
	//µÇÂ¼Bomb
	void BombEnter() {

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
