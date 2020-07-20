#include "pch.h"
#include "Player.h"
#include "Manager.h"


namespace NspPlayer {

	Player::Player() : Unit()
	{
		this->flag = 0;
		this->bomb_flag = 0;
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
		slow_center_point = { t_w / 2.0f, t_h / 2.0f};
		slow_center_rect = { 0,0,(float)t_w, (float)t_h };
		x = (float)FX + FW / 2.0f;
		y = (float)FY + FW - 50.0f;
		this->range = 2.0f;
		//player_bullet = new NspBullet::Bullet[PLAYER_BULLET_MAX];

		
	}

	int Player::GetControl() {
		SDL_PumpEvents();
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
		float mx = 0.0, my = 0.0, speed = 4.5f;
		int key_num = GetControl();

		if (this->state == PLAYER_DEATH) { //刚死亡的瞬间
			this->state = PLAYER_INVINCIBLE_MOVE;//进入无敌状态
			this->x = (float)FMX / 2.0f;//设置坐标
			this->y = (float)FMY + this->h;
			this->invincible_cnt = 0;
		}

		if (this->state == PLAYER_INVINCIBLE_MOVE) {
			this->y -= 1.5f;//将角色往上移动
			if (this->invincible_cnt > 60 || ((this->y < (float)FMY) && key_num!=0)) {
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
			speed /= sqrt(2.0f);
		if (!key[RIGHT] && !key[LEFT])
			prev_state = 0;
		if (!(key[RIGHT] && key[LEFT])) {
			if (key[RIGHT]) {
				if (prev_state != RIGHT)
					move_start = 0;
				mx = speed;
				if (move_start < FRAME_SPEED / 2.0f * 4) {
					frame_now = (int)(8 * 2 + move_start / (FRAME_SPEED / 2.0f));
					move_start++;
				}
				else {
					frame_now = (frame % (FRAME_SPEED * 4)) / FRAME_SPEED + 8 * 2 + 4;
				}
				prev_state = RIGHT;
			}
			if (key[LEFT]) {
				if (prev_state != LEFT)
					move_start = 0;
				mx = -speed;
				if (move_start < FRAME_SPEED / 2 * 4) {
					frame_now = (int)(8 * 1 + move_start / (FRAME_SPEED / 2.0f));
					move_start++;
				}
				else {
					frame_now = (frame % (FRAME_SPEED * 4)) / FRAME_SPEED + 8 * 1 + 4;
				}
				prev_state = LEFT;
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
			slow_center_rect.x = x - slow_center_size.w / 2.0f;
			slow_center_rect.y = y - slow_center_size.h / 2.0f;
		}
		else
			slow = false;
		if (!(x + mx < (float)FX || x + mx>(float)FMX))
			x += mx;
		if (!(y + my< (float)FY || y + my>(float)FMY))
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
			if (this->invincible_cnt % 2 == 0)  // 无敌状态时闪烁
				Unit::Render();
		}else
			Unit::Render(); //正常显示
		if (slow) { // 慢速移动时，显示中心贴图
			SDL_RenderCopyExF(renderer, center, &slow_center_size, &slow_center_rect,(frame % 360) * 5.0, &slow_center_point, SDL_FLIP_NONE);
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
			temp.angle = -PI / 2.0f;
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