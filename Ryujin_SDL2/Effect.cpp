#include "pch.h"
#include "Effect.h"
#include "Sound.h"

namespace NspEffect {
	float rang(double ang) {
		return (float)(-ang + ang * 2 * (rand() % 10000) / 10000.0);
	}

	Effect::Effect() {

		this->flag = false;
		this->col = 0;
		this->knd = 0;
		this->eff = 0;
		this->brt = 0;

	}
	Effect::~Effect() {

		Unit::Free();

	}
	void  Effect::Init(effect_t* data) {
		/*
		int flag, cnt, col, knd, img, eff, brt;
		float x, y, r, ang;
		*/

		this->knd = data->knd;
		if (data->img != "") {
			Unit::Load(data->img);
		}
		else {
			Unit::Load(effect_image_list[this->knd]);
		}
		
		Unit::Init(UNIT_EFFECT);

		this->flag = true;
		this->frame = -data->wait;//等待帧数
		this->col = data->col;
		this->frame_now = this->col;
		this->knd = data->knd;
		this->eff = data->eff;
		this->brt = data->brt;
		this->x = data->x;
		this->y = data->y;
		this->scale = data->r == 0 ? 1 : data->r;
		this->angle = data->ang;
		this->move_angle = data->mvang;
	}
	void Effect::Update() {
		Unit::Update();
		switch (this->knd) {//根据效果的种类进行分歧
		case 0://0号的处理

			this->scale += 0.04f;//逐渐把效果的大小变大
			if (this->frame > 10)//如果计数为10以上
				this->brt -= 25;//将亮度降低
			if (this->frame > 20)//效果为20以上
				this->flag = false;//销毁之
			break;
		case 1:// Boom的特效
			//坐标计算
			this->x += cos(this->move_angle) * this->spd;
			this->y += sin(this->move_angle) * this->spd;
			//printf("%f %f\n", cos(this->move_angle) * this->spd, sin(this->move_angle));
			//速度计算
			if (this->frame < 60)
				this->spd -= (0.2f + this->frame * this->frame / 3000.0f);
			if (this->frame == 60) {
				this->spd = 0;
				Sound::PlayMusic(6);
				dn.flag = 1;
				dn.cnt = 0;
				dn.size = 11;
				dn.time = 20;
			}
			//亮度和大小的计算
			this->scale += 0.015f;
			if (this->frame < 51)
				this->brt += 5;
			if (this->frame >= 60) {
				this->scale += 0.04f;
				this->brt -= 255 / 30.0f;
			}
			//计数器自增以及消去计算
			if (this->frame >= 90)
				this->flag = false;

			break;
		case 2:// Boom特效（角色）
									//座標計算 坐标计算
			this->x += cos(this->move_angle) * this->spd;
			this->y += sin(this->move_angle) * this->spd;
			//亮度计算
			if (this->frame < 51)
				this->brt += 4;
			if (this->frame > 130 - 51)
				this->brt -= 4;
			//计数器自增及消去计算
			this->frame++;
			if (this->frame >= 130)
				this->flag = 0;
			break;
		case 3://Boom的特效（线）
				//坐标计算
			this->x += cos(this->move_angle) * this->spd;
			this->y += sin(this->move_angle) * this->spd;
			//亮度计算
			if (this->frame < 51)
				this->brt += 2;
			if (this->frame > 130 - 51)
				this->brt -= 2;
			//计数器自增与消去计算
			this->frame++;
			if (this->frame >= 130)
				this->flag = 0;
			break;
		default:
			LogA("effect设定错误");
			break;
		}

	}
	void Effect::Render() {

		Unit::Render(this->brt);

	}
}
