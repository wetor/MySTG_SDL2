// Ryujin_SDL2.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include "pch.h"
#include "global.h"
#include "Manager.h"
#include "Collider.h"
#include "Script.h"
#include <iostream>
#include <string>



#ifdef MUTEX
SDL_mutex *loop_lock = NULL;		//保护性互斥锁
SDL_cond *can_draw = NULL;
#endif


void Quit(int code)
{
	const char *errMsg = SDL_GetError();
	if (errMsg && strlen(errMsg)) {
		SDL_Log("Error : %s\n", errMsg);
	}
	Sound::SoundClose();
	TTF_CloseFont(font_default);
	TTF_CloseFont(font_mini);
	//销毁窗口、渲染器、纹理
	if (renderer) SDL_DestroyRenderer(renderer);
	if (window) SDL_DestroyWindow(window);
	

	SDL_Quit();
	exit(code);
}


/*========按键处理开始========*/
int UpdateLoop(void *data) {
	
	while (!quit) {
		Timer::Start("Update", "Wait");
#ifdef MUTEX
		SDL_mutexP(loop_lock);			//锁定
#endif
		NspWindow::FpsWait();//帧数控制
#ifdef MUTEX
		SDL_mutexV(loop_lock);			//解锁
		SDL_CondSignal(can_draw);
#endif
		Timer::End("Update", "Wait");
		//printf("%d\n", Timer::End("FPSWait"));
		SDL_Event event;
		while (SDL_PollEvent(&event)) {

			switch (event.type) {
			case SDL_KEYDOWN:			//按键按下
			{
				int key = event.key.keysym.sym;
				switch (key)
				{
				case SDLK_ESCAPE:		//ESC退出
					quit = true;
					return -1;
				default:
					break;
				}
			}
			default:
				break;
			}
		}
		Timer::Start("Update", "Environment");
		NspEnvironment::EnvUpdate(); 
		Timer::End("Update", "Environment");

		Timer::Start("Update", "Player");
		NspPlayer::PlayerUpdate(); 
		Timer::End("Update", "Player");

		Timer::Start("Update", "PlayerBullet");
		NspBullet::PlayerBulletUpdate(); 
		Timer::End("Update", "PlayerBullet");

		Timer::Start("Update", "Enemy");
		NspEnemy::EnemyUpdate(); 
		Timer::End("Update", "Enemy");

		Timer::Start("Update", "Emitter");
		NspEmitter::EmitterUpdate(); 
		Timer::End("Update", "Emitter");
		
		Timer::Start("Update", "Bullet");
		NspBullet::BulletUpdate(); 
		Timer::End("Update", "Bullet");
		
		Timer::Start("Update", "Collider");
		Collider::PlayerShotEnemy();
		Collider::PlayerBombEnemy();
		Collider::EnemyShotPlayer(); 
		Timer::End("Update", "Collider");
		
		Timer::Start("Update", "Effect");
		NspEffect::EffectUpdate(); 
		Timer::End("Update", "Effect");
		
		Timer::Start("Update", "Sound");
		Sound::Update(); 
		Timer::End("Update", "Sound");
		

		frame_total++;
	}
	return 0;
}
/*
绘制函数
*/
int DrawLoop(void *data) {
#if !defined(MUTEX)
	static int FPS = 1000 / 60;
	static Uint32 _FPS_Timer;
#endif
	while (!quit) {
		Timer::Start("Draw", "Wait");
#ifdef MUTEX
		SDL_CondWait(can_draw, loop_lock); 
#else
		if (SDL_GetTicks() - _FPS_Timer < FPS) {
			SDL_Delay(FPS - SDL_GetTicks() + _FPS_Timer);
		}
		_FPS_Timer = SDL_GetTicks();
#endif
		Timer::End("Draw", "Wait");
		SDL_RenderClear(renderer);
		
		SDL_RenderSetClipRect(renderer, &renderer_rect);
		Timer::Start("Draw", "Environment");
		NspEnvironment::EnvRender(); 
		Timer::End("Draw", "Environment");

		Timer::Start("Draw", "Effect");
		NspEffect::EffectRender(); 
		Timer::End("Draw", "Effect");

		Timer::Start("Draw", "Enemy");
		NspEnemy::EnemyRender(); 
		Timer::End("Draw", "Enemy");

		Timer::Start("Draw", "PlayerBullet");
		NspBullet::PlayerBulletRender(); 
		Timer::End("Draw", "PlayerBullet");

		Timer::Start("Draw", "Player");
		NspPlayer::PlayerRender(); 
		Timer::End("Draw", "Player");

		Timer::Start("Draw", "Bullet");
		NspBullet::BulletRender(); 
		Timer::End("Draw", "Bullet");

		


		//设置 game_surface mode
		/*
		Timer::Start("Draw", "Draw");
		SDL_LockSurface(game_surface);
		SDL_UpdateTexture(game_texture, &window_rect,
			(unsigned char*)game_surface->pixels + game_surface->pitch * window_rect.y + window_rect.x * 4,
			game_surface->pitch);
		SDL_UnlockSurface(game_surface);

		//game_texture = SDL_CreateTextureFromSurface(renderer, game_surface);

		SDL_RenderCopy(renderer, game_texture, &renderer_rect, &renderer_rect);
		Timer::End("Draw", "Draw");
		*/

		SDL_RenderSetClipRect(renderer, &window_rect);


		NspWindow::FpsShow(20, 20);
#ifdef DEBUG
		/*显示边框*/
		/*if (bright_set.brt < 255)
		{
			SDL_SetRenderDrawColor(render, bright_set.brt, bright_set.brt, bright_set.brt, 255);
			SDL_SetRenderDrawBlendMode(render, SDL_BLENDMODE_BLEND);
			
		}
		*/
		SDL_SetRenderDrawColor(renderer, 0, 0xFF, 0, 0xFF);

		SDL_Rect rect;
		rect = { FX, FY, FW, FH };
		SDL_RenderDrawRect(renderer, &rect);
		rect = { LX,LY,LW,LH };
		SDL_RenderDrawRect(renderer, &rect);
		rect = { RX,RY,RW,RH };
		SDL_RenderDrawRect(renderer, &rect);
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);

		NspEnemy::EnemyNumberShow(20, 40);
		NspEmitter::EmitterNumberShow(20, 60);
		NspBullet::BulletNumberShow(20, 80);
		//LogA("%d", Timer::Size());
		for (int i = 0; i < Timer::Size(); i++) {
			
			NumberShow(20, 150 + i * 20, Timer::Get(i));
		}

#endif

		SDL_RenderPresent(renderer);
	}


	return 0;
}

int main(int argc, char* argv[])
{
	if (!WindowInit())
		SDL_Log("ERROR:%s\n", SDL_GetError());
#ifdef MUTEX
	loop_lock = SDL_CreateMutex();
	can_draw = SDL_CreateCond();
#endif
	while (!quit) {

		switch (func_state) {
		case 0:
			LogA("SoundInit()");
			Sound::SoundInit();
			LogA("ResourcesInit()");
			ResourcesInit();
			
			/*lua脚本实现*/
			LogA("** ---- Scrip ---- **");
			/*LogA("ResourcesLoad");
			Script::Open("../Ryujin_SDL2/dat/script/load_res.lua");
			Script::Run();*/
			LogA("ScriptLoad");
			Script::Open("../Ryujin_SDL2/dat/script/load.lua");
			Script::Run();
			
			Script::Close();
			LogA("FuncState 0 Over");
			func_state = 1;
			break;
		case 1:
			LogA("EnvInit()");		NspEnvironment::EnvInit();
			LogA("EnemyInit()");	NspEnemy::EnemyInit();
			LogA("EmitterInit()");	NspEmitter::EmitterInit();
			LogA("PlayerInit()");	NspPlayer::PlayerInit();
			LogA("EffectInit()");	NspEffect::EffectInit();

			for(int i=0;i<100;i++)
				NspEnemy::EnemyEnter();
			LogA("FuncState 1 Over");
			func_state = 99;
			break;
		case 99:
			LogA("ThreadInit()");
			thread_draw = SDL_CreateThread(DrawLoop, "draw", NULL);
			LogA("FuncState 99 Over");

			func_state = 100;
			break;
		case 100:
		{
			UpdateLoop(NULL);
			
			break;
		}
		default:
			break;
		}

	}
	LogA("Quit");
	Quit(0);
	return 0;
}

