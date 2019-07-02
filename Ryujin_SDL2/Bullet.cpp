#include "pch.h"
#include "Bullet.h"

namespace NspBullet {
	Bullet::Bullet() : Unit()
	{
		this->flag = false;
		this->knd = 0;
		this->col = 0;
		this->state = 0;
		this->till = 0;
		this->eff = 0;
		this->spd = 0;
		this->base_angle[1] = 0;
		this->rem_spd[1] = 0;
	}


	Bullet::~Bullet()
	{
		Unit::Free();
	}
	void Bullet::Init(bullet_t* data) {
		Unit::Load("b1");
		w = 22;
		h = 22;
		Unit::Init(UNIT_BULLET);


		this->knd = data->knd;
		this->angle = data->angle;
		this->flag = true;
		this->x = data->x;
		this->y = data->y;

		this->col = data->col;
		frame_now = this->col;
		this->frame = 0;
		this->spd = 3.0;

	}

	void Bullet::Update() {

	}
	void Bullet::Free() {
		Unit::Free();

	}
}