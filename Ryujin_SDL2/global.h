#pragma once

#include "define.h"
#include "struct.h"
#include <SDL.h>
#include <SDL_thread.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <map>
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


extern  map<string, SDL_Surface*> image_surface;
extern  map<string, SDL_Texture*> image_texture;

extern double rang(double ang);