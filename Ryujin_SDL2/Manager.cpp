/*
管理者[待改名为Game]
一些控制游戏流程的函数
包括初始化和资源的加载


*/
#include "pch.h"
#include "define.h"
#include "global.h"
#include "Manager.h"



SDL_Window *window = NULL;
SDL_Renderer *render = NULL;
TTF_Font *font_default = NULL;
TTF_Font *font_mini = NULL;

SDL_Thread *thread_draw = NULL;
SDL_Thread *thread_draw2 = NULL;
SDL_Thread *thread_update = NULL;
SDL_Thread *thread_script = NULL;


map<string, SDL_Surface*> image_surface;
map<string, SDL_Texture*> image_texture;
bool quit = false;
//static TTF_Font *font = NULL;
//static TTF_Font *font_mini = NULL;
int frame_total = 0;
int func_state = 0;


bool WindowInit() {
	//初始化窗体+



	//SDL Init
	SDL_Init(SDL_INIT_EVERYTHING);
	//Settings
	/*SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 0);*/

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 32);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 2);
	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");


	TTF_Init();

	window = SDL_CreateWindow("Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_W, WINDOW_H, SDL_WINDOW_RESIZABLE);
	if (window == NULL) return false;

	//加载渲染器
	render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (render == NULL) return false;

	font_default = TTF_OpenFont("../Ryujin_SDL2/dat/font/default.ttf", 22);
	font_mini = TTF_OpenFont("../Ryujin_SDL2/dat/font/default.ttf", 12);
	
	if (font_default == NULL)  return false;
	
	//SDL_BlendMode(SDL_BLENDMODE_BLEND);
	return true;
}
void ResourcesInit() {
	image_surface.clear();
	image_texture.clear();
	image_surface["player"] = IMG_Load("../Ryujin_SDL2/dat/img/player/reimu.png");
	image_surface["enemy0"] = IMG_Load("../Ryujin_SDL2/dat/img/enemy/0.png");
	image_surface["b1"] = IMG_Load("../Ryujin_SDL2/dat/img/bullet/b1.png");
	image_surface["b3"] = IMG_Load("../Ryujin_SDL2/dat/img/bullet/b3.png");
	image_surface["b0"] = IMG_Load("../Ryujin_SDL2/dat/img/bullet/b0.png");
}
