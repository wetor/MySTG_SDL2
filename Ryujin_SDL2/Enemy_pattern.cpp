#include "pch.h"
#include "Enemy.h"
#include <stdlib.h>



namespace NspEnemy {
	double rang(double ang) {
		return (-ang + ang * 2 * (rand() % 10000) / 10000.0);
	}

	void enemy_pattern0(Enemy* _this) {
		int t = _this->frame;
		if (t == 0)
			_this->vy = 3;
		if (t == 40)
			_this->vy = 0;
		if (t == 40 + _this->wait)
			_this->vy = -3;
	}



	void enemy_pattern1(Enemy* _this) {
		int t = _this->frame;
		if (t == 0)
			_this->vy = 3;
		if (t == 40)
			_this->vy = 0;
		if (t == 40 + _this->wait) {
			_this->vx = -1;
			_this->vy = 2;
			_this->move_state = 0;
		}
	}



	void enemy_pattern2(Enemy* _this) {
		int t = _this->frame;
		if (t == 0)
			_this->vy = 3;
		if (t == 40)
			_this->vy = 0;
		if (t == 40 + _this->wait) {
			_this->vx = 1;
			_this->vy = 2;
			_this->move_state = 2;
		}
	}



	void enemy_pattern3(Enemy* _this) {
		int t = _this->frame;
		if (t == 0)
			_this->vy = 5;
		if (t == 30) {
			_this->move_state = 0;
		}
		if (t < 100) {
			_this->vx -= 5 / 100.0;
			_this->vy -= 5 / 100.0;
		}
	}



	void enemy_pattern4(Enemy* _this) {
		int t = _this->frame;
		if (t == 0)
			_this->vy = 5;
		if (t == 30) {
			_this->move_state = 2;
		}
		if (t < 100) {
			_this->vx += 5 / 100.0;
			_this->vy -= 5 / 100.0;
		}
	}



	void enemy_pattern5(Enemy* _this) {
		int t = _this->frame;
		if (t == 0) {
			_this->vx -= 1;
			_this->vy = 2;
			_this->move_state = 0;
		}
	}



	void enemy_pattern6(Enemy* _this) {
		int t = _this->frame;
		if (t == 0) {
			_this->vx += 1;
			_this->vy = 2;
			_this->move_state = 2;
		}
	}



	void enemy_pattern7(Enemy* _this) {
		int t = _this->frame;
		if (t == _this->wait) {
			_this->vx = -0.7;
			_this->vy = -0.3;
			_this->move_state = 0;
		}
	}



	void enemy_pattern8(Enemy* _this) {
		int t = _this->frame;
		if (t == _this->wait) {
			_this->vx = +0.7;
			_this->vy = -0.3;
			_this->move_state = 2;
		}
	}



	void enemy_pattern9(Enemy* _this) {
		int t = _this->frame;
		if (t == _this->wait)
			_this->vy = -1;
	}




	void enemy_pattern10(Enemy* _this) {
		int t = _this->frame;
		if (t == 0) _this->vy = 4;
		if (t == 40)_this->vy = 0;
		if (t >= 40) {
			if (t % 60 == 00) {
				int r = cos(_this->ang) < 0 ? 0 : 1;
				_this->sp = 6 + rang(2);
				_this->ang = rang(PI / 4) + PI * r;
				_this->move_state = 2 - 2 * r;
			}
			_this->sp *= 0.95;
		}
		if (t >= 40 + _this->wait) {
			_this->vy -= 0.05;
		}
	}

}