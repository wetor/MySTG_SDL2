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
		this->invincible_cnt = 0;
		this->shot_mode = 0;
		this->money = 0;
		this->slow = false;
		this->shot_cnt = 0;
		this->state = PLAYER_DEFAULT;
		this->center = NULL;
		this->slow_center_size = { 0,0,0,0 };
		this->slow_center_rect = { 0,0,0,0 };
		this->slow_center_point = { 0,0 };
	}
	void Player::Init()
	{
		Unit::Load("player");
		Unit::Init(UNIT_PLAYER);
		center = SDL_CreateTextureFromSurface(renderer, image_map["center"].surface);
		int t_w = image_map["center"].surface->w;
		int t_h = image_map["center"].surface->h;
		slow_center_size = { 0 , 0, t_w, t_h };
		slow_center_point = { t_w / 2, t_h / 2};
		x = (double)FX + FW / 2.0;
		y = (double)FY + FW - 50.0;
		this->range = 2.0;
		//player_bullet = new NspBullet::Bullet[PLAYER_BULLET_MAX];
	}

	int Player::GetControl() {
		const Uint8* key_state = SDL_GetKeyboardState(NULL);
		int num = 0;
		memset(key, false, sizeof(bool) * 7);
		if (key_state[SDL_SCANCODE_UP])
			key[UP] = true, num++;
		if (key_state[SDL_SCANCODE_DOWN])
			key[DOWN] = true, num++;
		if (key_state[SDL_SCANCODE_LEFT])
			key[LEFT] = true, num++;
		if (key_state[SDL_SCANCODE_RIGHT])
			key[RIGHT] = true, num++;
		if (key_state[SDL_SCANCODE_Z])
			key[SHOT] = true, num++;
		if (key_state[SDL_SCANCODE_X])
			key[BOOM] = true, num++;
		if (key_state[SDL_SCANCODE_LSHIFT])
			key[SLOW] = true, num++;
		return num;
	}

	void Player::Update() {
		static int move_start = 0;
		static int prev_state = 0;
		double mx = 0.0, my = 0.0, speed = 4.5f;
		int key_num = GetControl();

		if (this->state == PLAYER_DEATH) { //刚死亡的瞬间
			this->state = PLAYER_INVINCIBLE_MOVE;//进入无敌状态
			this->x = (double)FMX / 2.0;//设置坐标
			this->y = (double)FMY + this->h;
			this->invincible_cnt = 0;
		}

		if (this->state == PLAYER_INVINCIBLE_MOVE) {
			this->y -= 1.5;//将角色往上移动
			if (this->invincible_cnt > 60 || ((this->y < (double)FMY) && key_num!=0)) {
				this->state = PLAYER_INVINCIBLE;
			}
		}
		if (this->state == PLAYER_INVINCIBLE || this->state == PLAYER_INVINCIBLE_MOVE) {//如果无敌
			this->invincible_cnt++;
			if (this->invincible_cnt > 120)//如果已经2秒以上的话
				this->state = PLAYER_DEFAULT;
		}

		frame_now = (frame % (FRAME_SPEED * 8)) / FRAME_SPEED;

		if ((key[RIGHT] || key[LEFT]) && (key[DOWN] || key[UP]))
			speed /= sqrt(2.0);
		if (!key[RIGHT] && !key[LEFT])
			prev_state = 0;
		if (!(key[RIGHT] && key[LEFT])) {
			if (key[RIGHT]) {
				if (prev_state != SDL_SCANCODE_RIGHT)
					move_start = 0;
				mx = speed;
				if (move_start < FRAME_SPEED / 2.0 * 4) {
					frame_now = (int)(8 * 2 + move_start / (FRAME_SPEED / 2.0));
					move_start++;
				}
				else {
					frame_now = (frame % (FRAME_SPEED * 4)) / FRAME_SPEED + 8 * 2 + 4;
				}
				prev_state = SDL_SCANCODE_RIGHT;
			}
			if (key[LEFT]) {
				if (prev_state != SDL_SCANCODE_LEFT)
					move_start = 0;
				mx = -speed;
				if (move_start < FRAME_SPEED / 2 * 4) {
					frame_now = (int)(8 * 1 + move_start / (FRAME_SPEED / 2.0));
					move_start++;
				}
				else {
					frame_now = (frame % (FRAME_SPEED * 4)) / FRAME_SPEED + 8 * 1 + 4;
				}
				prev_state = SDL_SCANCODE_LEFT;
			}
		}

		if (!(key[DOWN] && key[UP])) {
			if (key[DOWN])
				my = speed;
			if (key[UP])
				my = -speed;
		}
		if (key[SLOW]) {
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
		if (key[SHOT]) {
			this->shot_cnt++;
			if (this->shot_cnt % 3 == 0) {//每3次计数射击一次
				Shot();
			}
		}
		else
			this->shot_cnt = 0;

		Unit::Update();

	}
	void Player::Render() {
		if ((this->state == PLAYER_INVINCIBLE || this->state == PLAYER_INVINCIBLE_MOVE) ) {
			if (this->invincible_cnt % 2 == 0)
				Unit::Render();
		}else
			Unit::Render();
		if (slow) {
			slow_center_rect = { (int)(x - slow_center_size.w / 2) , (int)(y - slow_center_size.h / 2), slow_center_size.w, slow_center_size.h };
			SDL_RenderCopyEx(renderer, center, &slow_center_size, &slow_center_rect,(frame % 360) * 5.0, &slow_center_point, SDL_FLIP_NONE);
		}
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