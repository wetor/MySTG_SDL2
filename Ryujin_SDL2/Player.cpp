#include "pch.h"
#include "Player.h"
#include "Manager.h"


namespace NspPlayer {
	
	Player::Player() : Unit()
	{
		this->flag = 0;
		this->power = 500;
		this->point = 0;
		this->score = 0;
		this->num = 0;
		this->mutekicnt = 0;
		this->shot_mode = 0;
		this->money = 0;
		this->slow = false;
		this->shot_cnt = 0;
	}
	void Player::Init()
	{
		Unit::Load("player");
		Unit::Init(UNIT_PLAYER);

		x = (double)FX + FW / 2.0;
		y = (double)FY + FW - 50.0;
		this->range = 2.0;
		player_bullet = new NspBullet::Bullet[PLAYER_BULLET_MAX];
	}
	void Player::Update() {



		static int move_start = 0;
		static int prev_state = 0;
		double mx = 0.0, my = 0.0, speed = 4.5f;


		const Uint8* key_state = SDL_GetKeyboardState(NULL);


		frame_now = (frame % (FRAME_SPEED * 8)) / FRAME_SPEED;

		if ((key_state[SDL_SCANCODE_RIGHT] || key_state[SDL_SCANCODE_LEFT]) && (key_state[SDL_SCANCODE_DOWN] || key_state[SDL_SCANCODE_UP]))
			speed /= sqrt(2.0);
		if (!key_state[SDL_SCANCODE_RIGHT] && !key_state[SDL_SCANCODE_LEFT])
			prev_state = 0;
		if (!(key_state[SDL_SCANCODE_RIGHT] && key_state[SDL_SCANCODE_LEFT])) {
			if (key_state[SDL_SCANCODE_RIGHT]) {
				if (prev_state != SDL_SCANCODE_RIGHT)
					move_start = 0;
				mx = speed;
				if (move_start < FRAME_SPEED / 2.0 * 4) {
					frame_now = 8 * 2 + move_start / (FRAME_SPEED / 2.0);
					move_start++;
				}
				else {
					frame_now = (frame % (FRAME_SPEED * 4)) / FRAME_SPEED + 8 * 2 + 4;
				}
				prev_state = SDL_SCANCODE_RIGHT;
			}
			if (key_state[SDL_SCANCODE_LEFT]) {
				if (prev_state != SDL_SCANCODE_LEFT)
					move_start = 0;
				mx = -speed;
				if (move_start < FRAME_SPEED / 2 * 4) {
					frame_now = 8 * 1 + move_start / (FRAME_SPEED / 2.0);
					move_start++;
				}
				else {
					frame_now = (frame % (FRAME_SPEED * 4)) / FRAME_SPEED + 8 * 1 + 4;
				}
				prev_state = SDL_SCANCODE_LEFT;
			}
		}

		if (!(key_state[SDL_SCANCODE_DOWN] && key_state[SDL_SCANCODE_UP])) {
			if (key_state[SDL_SCANCODE_DOWN])
				my = speed;
			if (key_state[SDL_SCANCODE_UP])
				my = -speed;
		}
		if (key_state[SDL_SCANCODE_LSHIFT]) {
			mx /= 3.0f;
			my /= 3.0f;
			slow = true;
		}
		else
			slow = false;
		if (!(x + mx < (double)FX || x + mx>(double)FMX))
			x += mx;
		if (!(y + my< (double)FY || y + my>(double)FMY))
			y += my;



		//当按下射击按钮的时候
		if (key_state[SDL_SCANCODE_Z]) {
			this->shot_cnt++;
			if (this->shot_cnt % 3 == 0) {//每3次计数射击一次
				Shot();
			}
		}
		else
			this->shot_cnt = 0;

		Unit::Update();

	}

	//一般射击的登录
	void Player::Shot() {
		static int cshot0num[2] = { 2,4 };
		static int cshot0pos_x[4] = { -10, 10,-30, 30 };
		static int cshot0pos_y[4] = { -30,-30,-10,-10 };
		for (int i = 0; i < cshot0num[this->power < 200 ? 0 : 1]; i++) {
			player_bullet_t temp;
			temp.flag = true;
			temp.cnt = 0;
			temp.angle = -PI / 2;
			temp.spd = 20;
			if (!this->slow) {
				temp.x = this->x + cshot0pos_x[i];
				temp.y = this->y + cshot0pos_y[i];
			}
			else {	//低速，子弹靠近中间
				temp.x = this->x + cshot0pos_x[i] / 3;
				temp.y = this->y + cshot0pos_y[i] / 2;
			}

			temp.power = 23;
			temp.knd = 0;
			NspBullet::PlayerBulletEnter(&temp);
		}
		
		Sound::PlayMusic(1);
		//se_flag[2] = 1;//播放发射音
	}



}