#include "pch.h"
#include "Bullet.h"
#include <string>
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
		this->rotate = 0;
		this->vx = 0;
		this->vy = 0;
		
	}


	Bullet::~Bullet()
	{
	}
	void Bullet::Init(bullet_t* data) {
		this->knd = data->knd;

		Unit::Load(bullet_info[this->knd].id);
		Unit::Init(UNIT_TYPE::BULLET);
		this->range = bullet_info[this->knd].range;

		
		this->angle = data->angle;
		
		this->x = data->x;
		this->y = data->y;
		this->vx = data->vx;
		this->vy = data->vy;
		this->state = data->state;
		this->rotate = data->rotate;
		this->col = data->col;
		frame_now = this->col;
		this->frame = 0;
		this->spd = data->spd;
		this->flag = true;

	}
	void Bullet::Init(player_bullet_t* data) {
		this->knd = data->knd;

		Unit::Load(player_bullet_image_list[this->knd]);
		Unit::Init(UNIT_TYPE::BULLET_PLAYER);
		this->range = 6.0;
		this->angle = data->angle;
		
		this->x = data->x;
		this->y = data->y;
		this->power= data->power;
		frame_now = 0;
		this->frame = 0;
		this->spd = data->spd;
		this->flag = true;
	}

	void Bullet::Update() {
		if (this->unit_type == UNIT_TYPE::BULLET_PLAYER) {
			float dranx = this->spd + 10.0f, drany = this->spd + 35.0f;
			this->x += cos(this->angle) * this->spd;
			this->y += sin(this->angle) * this->spd;
			if (this->x<(float)FX - dranx || this->x>(float)FMX + dranx ||
				this->y<-drany || this->y>(float)FMY + drany)//如果跑到画面外了的话
				this->flag = false;
		}
		else if (this->unit_type == UNIT_TYPE::BULLET) {
			// 由 Emitter 管理
			this->x += cos(this->angle) * this->spd;
			this->y += sin(this->angle) * this->spd;
			if (this->spd == 0 && (vx != 0 || vy != 0)) {
				//LogA("%f %f",vx,vy);
				this->x += vx;
				this->y += vy;
				angle = atan2(vy, vx);
			}
			//printf("cnt %d bullet x %lf y %lf angle %lf\n",frame, this->x, this->y, this->angle);
			if (this->x< (float)FX - 50 || this->x>(float)FMX + 50 || this->y< (float)FY - 50 || this->y>(float)FMY + 50) {//如果跑到画面外面的话
				if (this->till < this->frame) {//且比最低程度不会销毁的时间还要很长
					this->flag = false;//销毁之
					
					//printf("bullet remove enemy_id:%d bullet_id:%d\n", enemy_id,i);
				}
			}
			if (this->rotate == 1) {
				rotate_angle = 2.0f * PI * (frame % 120) / 120;
			}
			else {
				rotate_angle = 0;
			}
		}
		Unit::Update();

	}

}