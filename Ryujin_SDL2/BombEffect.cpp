#include "pch.h"
#include "Effect.h"
#include "Manager.h"

namespace NspEffect {
	

	BombEffect::BombEffect()
	{
		memset(effect_id, -1, sizeof(int) * (3 + 4));
		bom = bom_t();
		//this->Init();
	}
	void BombEffect::Bomb()
	{
		if (bom.flag == 1) return;
		bom.flag = 1;
		bom.cnt = 0;
		bom.knd = 0;
		player->state = PLAYER_STATE::BOMB;
		NspBullet::BulletClear();
		//NspEmitter::EmitterClear();
		Sound::PlayMusic(5);//播放确定声
		//竖线
		effect_t temp1, temp2, temp3;
		temp1.img = "bom_title0";
		temp1.knd = 3;// Boom的线的特效 bom_title0.png
		temp1.brt = 0;//α值
		temp1.ang = PI / 2;//图像的方向
		temp1.mvang = -PI / 2;//特效前进的方向
		temp1.spd = 1;//速度
		temp1.r = 1;//大小
		temp1.eff = 2;//α混合
		temp1.x = FX + 70;//坐标
		temp1.y = FY + 300;
		effect_id[0] = EffectEnter(&temp1);
		//横线
		temp2.img = "bom_title0";
		temp2.knd = 3;// Boom的线的特效
		temp2.brt = 0;
		temp2.ang = 0;
		temp2.mvang = 0;
		temp2.spd = 1;
		temp2.r = 1;
		temp2.eff = 2;
		temp2.x = FX + 100;
		temp2.y = FY + 350;
		effect_id[1] = EffectEnter(&temp2);
		//角色
		temp3.img = "body";
		temp3.knd = 2;//Boom的角色、线的特效
		temp3.brt = 0;
		temp3.ang = 0;
		temp3.mvang = -PI / 2;
		temp3.spd = 0.7f;
		temp3.r = 1;
		temp3.eff = 2;
		temp3.x = FX + 260;
		temp3.y = FY + 300;
		effect_id[2] = EffectEnter(&temp3);
	}

	void BombEffect::Update()
	{
		static int n, k;
		static float shot_angle[4] = { 0,PI,PI / 2,PI * 1.5f };//4发特效飞行的角度
		if (bom.flag == 1) {//如果Boom已经被登录
			// 登录
			if (bom.cnt % 10 == 0) {//1/6秒一次
				n = (bom.cnt / 10);
				if (n < 4) {
					effect_t temp;
					temp.flag = 1;
					temp.wait= 0;
					temp.knd = 1;//特效编号1：Boom的特效
					temp.brt = 0;
					temp.ang = rang(PI);//随机的图像方向
					temp.mvang = shot_angle[n] - PI / 4;//飞行方向
					temp.spd = 13 + rang(2);//速度
					temp.r = 0.5;//大小
					temp.eff = 2;//α混合
					temp.img = n < 3 ? "bom0" : "bom1";//图像
					temp.x = player->x;//坐标
					temp.y = player->y;
					effect_id[3+n] = EffectEnter(&temp);
				}
			}
			bom.cnt++;
			if (bom.cnt < 40)
				bright_set.brt = 255 - bom.cnt * 5;//设定画面的亮度（暗）
			if (bom.cnt > 90)
				bright_set.brt = 255 - 40 * 5 + (bom.cnt - 90) * 5;//设定画面的的亮度（亮）
			if (bom.cnt > 130) {
				player->state = PLAYER_STATE::DEFAULT;
				bom.flag = 0;
				bright_set.brt = 255;
			}
			// 更新
			for (int i : effect_id) {
				if (!(i >= 0 && effect[i].flag)) continue;
				switch (effect[i].knd) {//根据效果的种类进行分歧
				case 1:// Boom的特效
					//坐标计算
					effect[i].x += cos(effect[i].move_angle) * effect[i].spd;
					effect[i].y += sin(effect[i].move_angle) * effect[i].spd;
					//printf("%f %f\n", cos(effect[i].move_angle) * effect[i].spd, sin(effect[i].move_angle));
					//速度计算
					if (effect[i].frame < 60)
						effect[i].spd -= (0.2f + effect[i].frame * effect[i].frame / 3000.0f);
					if (effect[i].frame == 60) {
						effect[i].spd = 0;
						Sound::PlayMusic(6);
						dn.flag = 1;
						dn.cnt = 0;
						dn.size = 11;
						dn.time = 20;
					}
					//亮度和大小的计算
					effect[i].scale += 0.015f;
					if (effect[i].frame < 51)
						effect[i].brt += 5;
					if (effect[i].frame >= 60) {
						effect[i].scale += 0.04f;
						effect[i].brt -= 255 / 30.0f;
					}
					//计数器自增以及消去计算
					if (effect[i].frame >= 90)
						effect[i].flag = false;

					break;
				case 2:// Boom特效（角色）
											//座標計算 坐标计算
					effect[i].x += cos(effect[i].move_angle) * effect[i].spd;
					effect[i].y += sin(effect[i].move_angle) * effect[i].spd;
					//亮度计算
					if (effect[i].frame < 51)
						effect[i].brt += 4;
					if (effect[i].frame > 130 - 51)
						effect[i].brt -= 4;
					//计数器自增及消去计算
					if (effect[i].frame >= 130)
						effect[i].flag = 0;
					break;
				case 3://Boom的特效（线）
						//坐标计算
					effect[i].x += cos(effect[i].move_angle) * effect[i].spd;
					effect[i].y += sin(effect[i].move_angle) * effect[i].spd;
					//亮度计算
					if (effect[i].frame < 51)
						effect[i].brt += 2;
					if (effect[i].frame > 130 - 51)
						effect[i].brt -= 2;
					//计数器自增与消去计算
					if (effect[i].frame >= 130)
						effect[i].flag = 0;
					break;
				default:
					LogA("effect设定错误");
					break;
				}
			}

		}

	}

}