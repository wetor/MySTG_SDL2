#pragma once

#include "define.h"
#include "struct.h"
#include "Utils.h"
#include <map>
#include <vector>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_thread.h>
#include <SDL_ttf.h>
#include <stdio.h>
using namespace std;

extern  SDL_Window *window;
extern  SDL_Renderer *render;


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
extern  vector<string> bullet_image_list;
extern  vector<string> player_bullet_image_list;

