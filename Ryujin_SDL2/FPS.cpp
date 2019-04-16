#include "pch.h"

#include "Manager.h"
// fps
#define FLAME 60

//fps的计数器，60帧1次记录作为基准的时刻
int fps_count, count0t;
//为了进行平均计算,记录60次1个周期的时间
int f[FLAME];
//平均fps
double ave;


int fps_count_loop, count0t_loop;


//以FLAME fps为目标进行fps的计算和控制
void FpsWait() {
	int term, i, gnt;
	static int t = 0;
	if (fps_count == 0) {//60帧1次的话
		if (t == 0)//如果是最开始的话不等待
			term = 0;
		else//基于上一次记录了的时间计算
			term = count0t + 1000 - SDL_GetTicks();
	}
	else    //应该等待的时间=当前的理论时刻-当前的实际时刻（译者注：GetNowCount()是DX Library中类似GetTickCount()的函数，用于返回系统启动后到当前为止的毫秒精度的时间计数）
		term = (int)(count0t + fps_count * (1000.0 / FLAME)) - SDL_GetTicks();

	if (term > 0)//只等待应该等待的时间（译者注：如果term大于0的话，说明当前帧率应该到达的值还超过了当前的时刻，那么就等待这个差值即可；反过来则无需等待，因为说明当前帧等待的时间早就被超过了，之所以出现这种情况一般是因为绘制过程太多影响了效率）
		SDL_Delay(term);
	gnt = SDL_GetTicks();
	if (fps_count == 0)// 60帧进行1次基准变更
		count0t = gnt;
	f[fps_count] = gnt - t;//记录1个周期的时间
	t = gnt;
	//平均计算
	if (fps_count == FLAME - 1) {
		ave = 0;
		for (i = 0; i < FLAME; i++)
			ave += f[i];
		ave /= FLAME;
	}
	fps_count = (++fps_count) % FLAME;
}

void FpsWaitOnly() {
	int term, i, gnt;
	static int t = 0;
	if (fps_count_loop == 0) {//60帧1次的话
		if (t == 0)//如果是最开始的话不等待
			term = 0;
		else//基于上一次记录了的时间计算
			term = count0t_loop + 1000 - SDL_GetTicks();
	}
	else    //应该等待的时间=当前的理论时刻-当前的实际时刻（译者注：GetNowCount()是DX Library中类似GetTickCount()的函数，用于返回系统启动后到当前为止的毫秒精度的时间计数）
		term = (int)(count0t_loop + fps_count_loop * (1000.0 / FLAME)) - SDL_GetTicks();

	if (term > 0)//只等待应该等待的时间（译者注：如果term大于0的话，说明当前帧率应该到达的值还超过了当前的时刻，那么就等待这个差值即可；反过来则无需等待，因为说明当前帧等待的时间早就被超过了，之所以出现这种情况一般是因为绘制过程太多影响了效率）
		SDL_Delay(term);
	gnt = SDL_GetTicks();
	if (fps_count_loop == 0)// 60帧进行1次基准变更
		count0t_loop = gnt;
	t = gnt;
	//平均计算
	fps_count_loop = (++fps_count_loop) % FLAME;
}

//在x,y的位置显示fps
void FpsShow(int x, int y) {
	if (ave != 0) {
		char text[10];
		snprintf(text, 10, "[%.3f]", 1000 / ave);
		//printf(text);
		SDL_Surface *surf = NULL; 
		//TTF_RenderText_Solid
		surf = TTF_RenderText_Solid(font_default, text, { 255, 0, 0,255 });
		SDL_Texture *texture = SDL_CreateTextureFromSurface(render, surf);
		SDL_Rect dst = { x,y,surf->w,surf->h };
		SDL_RenderCopy(render, texture, NULL, &dst);
		SDL_FreeSurface(surf);
		SDL_DestroyTexture(texture);
	}
	return;
}