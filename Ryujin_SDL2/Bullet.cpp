#include "pch.h"
#include "Bullet.h"


Bullet::Bullet()
{
}


Bullet::~Bullet()
{
}
void Bullet::Init(bullet_t * data) {
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