#include "pch.h"
#include "Environment.h"
#include "Manager.h"

namespace NspEnvironment {


	void Environment::Init() {
		Unit::Load("back0");
		Unit::Init(UNIT_TYPE::ENV);
		frame_now = 0;
	}
	void Environment::Update() {

		Unit::Update();
	}
	void Environment::Render() {
		if (this->frame < 0) return;			//frame为负数即等待帧数

		
		SDL_Rect temp_rect = { FX , frame % h,this->w, this->h };
		
		if (bright_set.brt < 255)
		{
			SDL_SetTextureColorMod(texture, bright_set.brt, bright_set.brt, bright_set.brt);
			SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
		}
		else {
			SDL_SetTextureColorMod(texture, 255,255,255);
			SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
		}
		//SDL_BlitSurface(surface, &frame_rect[frame_now], game_surface, &temp_rect);
		SDL_RenderCopy(renderer, texture, &frame_rect[frame_now], &temp_rect);
		temp_rect.y -= h;
		SDL_RenderCopy(renderer, texture, &frame_rect[frame_now], &temp_rect);
		//SDL_BlitSurface(surface, &frame_rect[frame_now], game_surface, &temp_rect);
		

	}


}