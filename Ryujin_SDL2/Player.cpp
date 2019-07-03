#include "pch.h"
#include "Player.h"
namespace NspPlayer {

	Player::Player() : Unit()
	{
		this->flag = 0;
		this->power = 0;
		this->point = 0;
		this->score = 0;
		this->num = 0;
		this->mutekicnt = 0;
		this->shot_mode = 0;
		this->money = 0;
		this->slow = false;
	}
	void Player::Init()
	{
		Unit::Load("player");
		Unit::Init(UNIT_PLAYER);

		x = (double)FX + FW / 2.0;
		y = (double)FY + FW - 50.0;
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



		Unit::Update();

	}

}