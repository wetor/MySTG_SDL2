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
		this->knd = data->knd;

		Unit::Load(bullet_image_list[this->knd]);
		Unit::Init(UNIT_BULLET);
		

		
		this->angle = data->angle;
		this->flag = true;
		this->x = data->x;
		this->y = data->y;
		this->state = data->state;
		this->col = data->col;
		frame_now = this->col;
		this->frame = 0;
		this->spd = 3.0;

	}

	void Bullet::Update() {
		Unit::Update();
	}
	void Bullet::Free() {
		Unit::Free();

	}
}