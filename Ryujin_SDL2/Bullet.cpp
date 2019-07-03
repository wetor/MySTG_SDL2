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

		this->power = 0;
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
		this->spd = data->spd;

	}
	void Bullet::Init(player_bullet_t* data) {
		this->knd = data->knd;

		Unit::Load(player_bullet_image_list[this->knd]);
		Unit::Init(UNIT_PLAYER_BULLET);

		this->angle = data->angle;
		this->flag = true;
		this->x = data->x;
		this->y = data->y;
		this->power= data->power;
		frame_now = 0;
		this->frame = 0;
		this->spd = data->spd;

	}

	void Bullet::Update() {
		if (this->unit_type == UNIT_PLAYER_BULLET) {
			
			
			int dranx = this->spd + 11 / 2, drany = this->spd + 55 / 2;
			this->x += cos(this->angle) * this->spd;
			this->y += sin(this->angle) * this->spd;
			if (this->x<-dranx || this->x>(double)FMX - 50 + dranx ||
				this->y<-drany || this->y>(double)FMY - 50 + drany)//如果跑到画面外了的话
				this->flag = 0;
		}
		Unit::Update();
		
		

		
	}
	void Bullet::Free() {
		Unit::Free();

	}
}