// Ryujin_SDL2.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//


#include "pch.h"
#include "global.h"
#include "Manager.h"
#include "Script.h"
#include <iostream>
#include <string>


#ifdef MUTEX
SDL_mutex *bufferLock = NULL;		//保护性互斥锁
SDL_cond *can_update = NULL;		//条件变量
SDL_cond *can_draw = NULL;
#endif
static int FPS = 1000 / 60;
static Uint32 _FPS_Timer;


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

void print(std::string str) {
	std::cout << str << std::endl;
}
/*========按键处理开始========*/
int UpdateLoop(void *data) {
	
	while (!quit) {
		//事件处理等
		/*if (SDL_GetTicks() - _FPS_Timer < FPS) {
			SDL_Delay(FPS - SDL_GetTicks() + _FPS_Timer);
		}
		_FPS_Timer = SDL_GetTicks();*/
		
		/* 实时显示子弹数
		int num = 0;
		for (int i = 0; i < BULLET_MAX; i++) 
			if (bullet[i].flag) 
				num++;
		printf("%d\n",num);
		*/
		//FpsWaitOnly();
		FpsWait();//关联帧率显示
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
#ifdef MUTEX
		SDL_mutexP(bufferLock);			//锁定
#endif
		EmitterUpdate();
		EnemyUpdate();
#ifdef MUTEX
		SDL_mutexV(bufferLock);			//解锁
		SDL_CondSignal(can_draw);		//向draw发信号
#endif
		frame_total++;
	}
	return 0;
}
/*========绘制开始========*/
int DrawLoop(void *data) {

	while (!quit) {
		//事件处理等
		FpsWaitOnly();//仅控制帧率
		//SDL_Delay(16);
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
#ifdef MUTEX
		SDL_mutexP(bufferLock);			//锁定
#endif
		EnemyDraw();
		BulletDraw();
#ifdef MUTEX
		SDL_mutexV(bufferLock);			//解锁
		SDL_CondSignal(can_update);		//向update信号
#endif
		player->Draw();
		FpsShow(100, 100);
		SDL_RenderPresent(render);
	}


	return 0;
}
int draw2(void *data) {
	while (!quit) {
		if (SDL_GetTicks() - _FPS_Timer < FPS) {
			SDL_Delay(FPS - SDL_GetTicks() + _FPS_Timer);
		}
		_FPS_Timer = SDL_GetTicks();
		BulletDraw();
		SDL_RenderPresent(render);
	
	}

	
	return 0;
}

int main(int argc, char* argv[])
{
	if (!WindowInit())
		SDL_Log("ERROR:%s\n", SDL_GetError());
#ifdef MUTEX
	//创建互斥锁
	bufferLock = SDL_CreateMutex();
	//创建条件变量
	can_update = SDL_CreateCond();
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
			//thread_draw2 = SDL_CreateThread(draw2, "draw2", NULL);
			//thread_update = SDL_CreateThread(UpdateLoop, "update", NULL);
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

