#ifndef __GLOBAL_H__
#define __GLOBAL_H__

#include "define.h"
#include "struct.h"
#include "Tools.h"
#include <map>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_thread.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <vector>
using namespace std;


#ifdef MUTEX
extern  SDL_mutex* loop_lock;		//保护性互斥锁
#endif

extern  SDL_Rect renderer_rect;
extern  SDL_Rect window_rect;

extern  SDL_Window *window;
extern  SDL_Renderer *renderer;
extern	SDL_Surface *game_surface;
extern	SDL_Texture *game_texture;


extern  SDL_Thread *thread_draw;
extern  SDL_Thread *thread_emitter;
extern  SDL_Thread *thread_update;
extern  SDL_Thread *thread_script;

extern  bool quit;
extern TTF_Font *font_default;
extern TTF_Font *font_mini;

extern  int func_state;
extern  int frame_total;


extern  map<string, image_t> image_map;
extern  vector<bullet_info_t> bullet_info;
extern  vector<string> player_bullet_image_list;
extern  vector<string> effect_image_list;

extern bright_set_t bright_set; //绘制的亮度
#endif