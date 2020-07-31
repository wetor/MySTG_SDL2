#include "pch.h"
#include "Effect.h"
#include "Manager.h"

namespace NspEffect {
	BossEffect::BossEffect() {
		memset(effect_id, -1, sizeof(int) * 5);
	}
	void BossEffect::Init() {
		effect_t temp1, temp2, temp3, temp4, temp5;
		temp1.img = "boss_bg2";
		temp1.knd = 99;
		temp1.eff = 2; //brt表示 透明
		temp1.brt = 150;
		temp1.r = 1;
		effect_id[0] = EffectEnter(&temp1);

		temp2.img = "boss_bg1";
		temp2.knd = 99;
		temp2.eff = 2; //brt表示 透明
		temp2.brt = 150;
		temp2.r = 1;
		effect_id[1] = EffectEnter(&temp2);

		temp3.img = "boss_bg3";
		temp3.knd = 99;
		temp3.eff = 2; //brt表示 透明
		temp3.brt = 150;
		temp3.r = 1;
		effect_id[2] = EffectEnter(&temp3);

		temp4.img = "boss_bg3";
		temp4.knd = 99;
		temp4.eff = 2; //brt表示 透明
		temp4.brt = 150;
		temp4.r = 1;
		effect_id[3] = EffectEnter(&temp4);

		temp5.img = "boss_bg3";
		temp5.knd = 99;
		temp5.eff = 1; //brt表示 高亮
		temp5.brt = 0;
		temp5.r = 1;
		effect_id[4] = EffectEnter(&temp5);

		flag = true;
	}
	void BossEffect::Update() {

		int frame = boss->frame;
		int i = effect_id[0];
		effect[i].x = boss->dx;
		effect[i].y = boss->dy;
		effect[i].scale = (0.4f + 0.05f * sin(PI2 / 360 * (frame % 360))) * 3;
		effect[i].angle = 2 * PI * (frame % 580) / 580;

		i = effect_id[1];
		effect[i].x = boss->dx;
		effect[i].y = boss->dy;
		effect[i].scale = (0.5f + 0.1f * sin(PI2 / 360 * (frame % 360))) * 2;
		effect[i].angle = 2 * PI * (frame % 340) / 340;

		i = effect_id[2];
		effect[i].x = boss->dx + 60 * sin(PI2 / 153 * (frame % 153));
		effect[i].y = boss->dy + 80 * sin(PI2 / 120 * (frame % 120));
		effect[i].scale = 0.4f + 0.05f * sin(PI2 / 120 * (frame % 120));
		effect[i].angle = 2 * PI * (frame % 30) / 30;

		i = effect_id[3];
		effect[i].x = boss->dx + 60 * sin(PI2 / 200 * ((frame + 20) % 200));
		effect[i].y = boss->dy + 80 * sin(PI2 / 177 * ((frame + 20) % 177));
		effect[i].scale = 0.3f + 0.05f * sin(PI2 / 120 * (frame % 120));
		effect[i].angle = 2 * PI * (frame % 35) / 35;

		i = effect_id[4];
		effect[i].x = boss->dx + 60 * sin(PI2 / 230 * ((frame + 40) % 230));
		effect[i].y = boss->dy + 80 * sin(PI2 / 189 * ((frame + 40) % 189));
		effect[i].scale = 0.6f + 0.05f * sin(PI2 / 120 * (frame % 120));
		effect[i].angle = 2 * PI * (frame % 40) / 40;
	}

	void BossEffect::Clear()
	{
		for (int i = 0; i < 5; i++) {
			effect[effect_id[i]].flag = false;
		}
		flag = false;
	}

}