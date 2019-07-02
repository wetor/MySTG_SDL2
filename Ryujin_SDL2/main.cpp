// Ryujin_SDL2.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//


#include "pch.h"
#include "global.h"
#include "Manager.h"
#include "Script.h"
#include <iostream>
#include <string>


#define MUTEX
#ifdef MUTEX
SDL_mutex *loop_lock = NULL;		//保护性互斥锁
SDL_cond *can_emitter = NULL;		//条件变量
SDL_cond *can_draw = NULL;
#endif


void Quit(int code)
{
	const char *errMsg = SDL_GetError();
	if (errMsg && strlen(errMsg)) {
		SDL_Log("Error : %s\n", errMsg);
	}
	//TTF_CloseFont(font);
	//TTF_CloseFont(font_mini);
	//销毁窗口、渲染器、纹理
	if (window) SDL_DestroyWindow(window);
	if (render) SDL_DestroyRenderer(render);

	SDL_Quit();
	exit(code);
}


/*========按键处理开始========*/
int UpdateLoop(void *data) {
	
	while (!quit) {
#ifdef DEBUG
		// 实时显示子弹数
		int num = 0;
		for (int i = 0; i < BULLET_MAX; i++) 
			if (bullet[i].flag) 
				num++;
		printf("%d\n",num);
#endif

#ifdef MUTEX
		SDL_mutexP(loop_lock);			//锁定
#endif
		FpsWait();//帧数控制
#ifdef MUTEX
		SDL_mutexV(loop_lock);			//解锁
		SDL_CondSignal(can_emitter);
		SDL_CondSignal(can_draw);
#endif
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
		player->Update();
		EnemyUpdate();
		frame_total++;
	}
	return 0;
}
/*
绘制函数
*/
int DrawLoop(void *data) {

	while (!quit) {
#ifdef MUTEX
		SDL_CondWait(can_draw, loop_lock);
#else
		FpsWaitOnly();//仅控制帧率
#endif
		SDL_RenderClear(render);
#ifdef DEBUG
		/*显示边框*/
		SDL_SetRenderDrawColor(render, 0, 0xFF, 0, 0xFF);
		SDL_Rect rect;
		rect = { FX, FY, FW, FH };
		SDL_RenderDrawRect(render, &rect);
		rect = { LX,LY,LW,LH };
		SDL_RenderDrawRect(render, &rect);
		rect = { RX,RY,RW,RH };
		SDL_RenderDrawRect(render, &rect);
		SDL_SetRenderDrawColor(render, 0, 0, 0, 0);
#endif
		EnemyDraw();
		BulletDraw();

		player->Draw();
		FpsShow(100, 100);
		SDL_RenderPresent(render);
	}


	return 0;
}
/*
弹幕计算相关 更新函数
*/
int EmitterLoop(void* data) {
	static int FPS = 1000 / 60;
	static Uint32 _FPS_Timer;
	while (!quit) {
		if (func_state != 100) continue;
#ifdef MUTEX
		SDL_CondWait(can_emitter, loop_lock);
#else
		if (SDL_GetTicks() - _FPS_Timer < FPS) {
			SDL_Delay(FPS - SDL_GetTicks() + _FPS_Timer);
		}
		_FPS_Timer = SDL_GetTicks();
#endif
		EmitterUpdate();
	}
	return 0;
}

int main(int argc, char* argv[])
{
	if (!WindowInit())
		SDL_Log("ERROR:%s\n", SDL_GetError());
#ifdef MUTEX
	loop_lock = SDL_CreateMutex();
	can_emitter = SDL_CreateCond();
	can_draw = SDL_CreateCond();
#endif
	while (!quit) {

		switch (func_state) {
		case 0:
			printf("Func 0\n");
			ResourcesInit();
			//lua脚本实现
			Script::Open("../Ryujin_SDL2/dat/script/load.lua");
			Script::Run();
			Script::Close();

			func_state = 1;
			break;
		case 1:
			printf("Init 1\n");

			PlayerInit();
			EnemyInit();
			EmitterInit();
			for(int i=0;i<100;i++)
				EnemyEnter();
		
			func_state = 99;
			break;
		case 99:
			printf("Func 99\n");
			
			thread_draw = SDL_CreateThread(DrawLoop, "draw", NULL);
			thread_emitter = SDL_CreateThread(EmitterLoop, "emitter", NULL);
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
	printf("Quit\n");
	Quit(0);
	return 0;
}

