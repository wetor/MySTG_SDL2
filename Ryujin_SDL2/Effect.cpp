#include "pch.h"
#include "Effect.h"

namespace NspEffect {
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

		Unit::Load(effect_image_list[this->knd]);
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
		default:
			LogA("effect设定错误");
			break;
		}

	}
	void Effect::Render() {

		Unit::Render(this->brt);

	}
}
