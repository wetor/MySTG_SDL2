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
		this->state = PLAYER_STATE::DEFAULT;
		this->center = NULL;
		this->slow_center_size = { 0,0,0,0 };
		this->slow_center_rect = { 0,0,0,0 };
		this->slow_center_point = { 0,0 };
		this->bomb = new NspEffect::BombEffect();
		this->death_bomb = new NspEffect::DeathBombEffect();
	}
	void Player::Init()
	{
		Unit::Load("player");
		Unit::Init(UNIT_TYPE::PLAYER);
		center = SDL_CreateTextureFromSurface(renderer, image_map["center"].surface);
		ball = SDL_CreateTextureFromSurface(renderer, image_map["ball"].surface);
		int t_w = image_map["center"].surface->w;
		int t_h = image_map["center"].surface->h;
		slow_center_size = { 0 , 0, t_w, t_h };
		slow_center_point = { t_w / 2.0f, t_h / 2.0f};
		slow_center_rect = { 0,0,(float)t_w, (float)t_h };

		t_w = image_map["ball"].surface->w;
		t_h = image_map["ball"].surface->h;
		ball_size = { 0 , 0, t_w, t_h };
		ball_point = { t_w / 2.0f, t_h / 2.0f };
		ball_rect = { 0,0,(float)t_w, (float)t_h };

		x = (float)FX + FW / 2.0f;
		y = (float)FY + FW - 50.0f;
		this->range = 2.0f;
		//player_bullet = new NspBullet::Bullet[PLAYER_STATE::BULLET_MAX];

		
	}

	int Player::GetControl() {
		SDL_PumpEvents();
		const Uint8* key_state = SDL_GetKeyboardState(NULL);
		int num = 0;
		memset(key, false, sizeof(bool) * 7);
		if (key_state[SDL_SCANCODE_UP])
			key[(int)KEY_CONTROL::UP] = true, num++;
		if (key_state[SDL_SCANCODE_DOWN])
			key[(int)KEY_CONTROL::DOWN] = true, num++;
		if (key_state[SDL_SCANCODE_LEFT])
			key[(int)KEY_CONTROL::LEFT] = true, num++;
		if (key_state[SDL_SCANCODE_RIGHT])
			key[(int)KEY_CONTROL::RIGHT] = true, num++;
		if (key_state[SDL_SCANCODE_Z])
			key[(int)KEY_CONTROL::SHOT] = true, num++;
		if (key_state[SDL_SCANCODE_X])
			key[(int)KEY_CONTROL::BOMB] = true, num++;
		if (key_state[SDL_SCANCODE_LSHIFT])
			key[(int)KEY_CONTROL::SLOW] = true, num++;
		return num;
	}

	void Player::Update() {
		static int move_start = 0;
		static int prev_state = 0;
		float mx = 0.0, my = 0.0, speed = 4.5f;
		float ny = (sin(2.0f * PI * (frame % 50) / 50) * 3);
		int key_num = GetControl();

		if (this->state == PLAYER_STATE::DEATH_BOMB) {//如果正在进行决死处理
			bright_set.brt = 80;//变暗
			if (this->frame > 20) {//0.33秒中进行决死处理
				this->state = PLAYER_STATE::DEATH;    //1：正在进行决死处理 2：被击毁正在上浮中
				this->frame = 0;
				bright_set.brt = 255;
			}
		}

		if (this->frame == 0 && this->state == PLAYER_STATE::DEATH) { //刚死亡的瞬间
			this->state = PLAYER_STATE::INVINCIBLE_MOVE;//进入无敌状态
			this->x = (float)FMX / 2.0f;//设置坐标
			this->y = (float)FMY + this->h;
			this->invincible_cnt = 0;
		}

		if (this->state == PLAYER_STATE::INVINCIBLE_MOVE) {
			this->y -= 1.5f;//将角色往上移动
			if (this->invincible_cnt > 60 || ((this->y < (float)FMY) && key_num!=0)) {
				this->state = PLAYER_STATE::INVINCIBLE;
			}
		}
		if (this->state == PLAYER_STATE::INVINCIBLE || this->state == PLAYER_STATE::INVINCIBLE_MOVE) {//如果无敌
			this->invincible_cnt++;
			if (this->invincible_cnt > 120)//如果已经2秒以上的话
			{
				this->state = PLAYER_STATE::DEFAULT;
				this->invincible_cnt = 0;
			}
				
		}

		frame_now = (frame % (FRAME_SPEED * 8)) / FRAME_SPEED;

		if (this->state != PLAYER_STATE::DEATH_BOMB) { // 非决死 可以移动

			if ((key[(int)KEY_CONTROL::RIGHT] || key[(int)KEY_CONTROL::LEFT]) && (key[(int)KEY_CONTROL::DOWN] || key[(int)KEY_CONTROL::UP]))
				speed /= sqrt(2.0f);
			if (!key[(int)KEY_CONTROL::RIGHT] && !key[(int)KEY_CONTROL::LEFT])
				prev_state = 0;
			if (!(key[(int)KEY_CONTROL::RIGHT] && key[(int)KEY_CONTROL::LEFT])) {
				if (key[(int)KEY_CONTROL::RIGHT]) {
					if (prev_state != (int)KEY_CONTROL::RIGHT)
						move_start = 0;
					mx = speed;
					if (move_start < FRAME_SPEED / 2.0f * 4) {
						frame_now = (int)(8 * 2 + move_start / (FRAME_SPEED / 2.0f));
						move_start++;
					}
					else {
						frame_now = (frame % (FRAME_SPEED * 4)) / FRAME_SPEED + 8 * 2 + 4;
					}
					prev_state = (int)KEY_CONTROL::RIGHT;
				}
				if (key[(int)KEY_CONTROL::LEFT]) {
					if (prev_state != (int)KEY_CONTROL::LEFT)
						move_start = 0;
					mx = -speed;
					if (move_start < FRAME_SPEED / 2 * 4) {
						frame_now = (int)(8 * 1 + move_start / (FRAME_SPEED / 2.0f));
						move_start++;
					}
					else {
						frame_now = (frame % (FRAME_SPEED * 4)) / FRAME_SPEED + 8 * 1 + 4;
					}
					prev_state = (int)KEY_CONTROL::LEFT;
				}
			}

			if (!(key[(int)KEY_CONTROL::DOWN] && key[(int)KEY_CONTROL::UP])) {
				if (key[(int)KEY_CONTROL::DOWN])
					my = speed;
				if (key[(int)KEY_CONTROL::UP])
					my = -speed;
			}
			if (key[(int)KEY_CONTROL::SLOW]) {
				mx /= 3.0f;
				my /= 3.0f;
				slow = true;
				slow_center_rect.x = x - slow_center_size.w / 2.0f + dn.x;
				slow_center_rect.y = y - slow_center_size.h / 2.0f + dn.y;
				ball_rect.y = y + 15 + ny - ball_size.h / 2.0f + dn.y;
			}
			else {
				slow = false;
				ball_rect.y = y + 30 + ny - ball_size.h / 2.0f + dn.y;
			}
				
			if (!(x + mx < (float)FX || x + mx>(float)FMX))
				x += mx;
			if (!(y + my< (float)FY || y + my>(float)FMY))
				y += my;

		}



		//当按下射击按钮的时候
		if (key[(int)KEY_CONTROL::SHOT]) {
			this->shot_cnt++;
			if (this->shot_cnt % 3 == 0) {//每3次计数射击一次
				Shot();
			}
		}
		else
			this->shot_cnt = 0;

		//当按下Bomb按钮的时候 决死 或者 普通时可用
		if (key[(int)KEY_CONTROL::BOMB] && (this->state == PLAYER_STATE::DEATH_BOMB || this->state == PLAYER_STATE::DEFAULT)) {
			bomb->Bomb();
		}
		bomb->Update();
		Unit::Update();

	}
	void Player::Render() {

		if (slow)
			ball_rect.x = x + dn.x - ball_size.w / 2.0f - 15;
		else
			ball_rect.x = x + dn.x - ball_size.w / 2.0f - 30;
		SDL_RenderCopyExF(renderer, ball, &ball_size, &ball_rect, (frame % 360) * 5.0f, &ball_point, SDL_FLIP_NONE);
		if (slow)
			ball_rect.x = x + dn.x - ball_size.w / 2.0f + 15;
		else
			ball_rect.x = x + dn.x - ball_size.w / 2.0f + 30;
		SDL_RenderCopyExF(renderer, ball, &ball_size, &ball_rect, -(frame % 360) * 5.0f, &ball_point, SDL_FLIP_NONE);
		if ((this->state == PLAYER_STATE::INVINCIBLE || this->state == PLAYER_STATE::INVINCIBLE_MOVE) ) {
			if (this->invincible_cnt % 2 == 0)  // 无敌状态时闪烁
				Unit::Render();
		}else
			Unit::Render(); //正常显示
		if (slow) { // 慢速移动时，显示中心贴图
			SDL_RenderCopyExF(renderer, center, &slow_center_size, &slow_center_rect,(frame % 360) * 5.0f, &slow_center_point, SDL_FLIP_NONE);
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