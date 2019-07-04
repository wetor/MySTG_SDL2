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
SDL_Thread *thread_emitter = NULL;
SDL_Thread *thread_update = NULL;
SDL_Thread *thread_script = NULL;


map<string, image_t> image_map;
vector<string> bullet_image_list;
vector<string> player_bullet_image_list;

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
	SDL_RenderSetLogicalSize(render, WINDOW_W, WINDOW_H);
	font_default = TTF_OpenFont("../Ryujin_SDL2/dat/font/default.ttf", 22);
	font_mini = TTF_OpenFont("../Ryujin_SDL2/dat/font/default.ttf", 12);
	
	if (font_default == NULL)  return false;
	
	//SDL_BlendMode(SDL_BLENDMODE_BLEND);
	return true;
}
void ResourcesInit() {
	image_map.clear();
	player_bullet_image_list.clear();

	image_map["player"] = { 32,48,IMG_Load("../Ryujin_SDL2/dat/img/player/reimu.png") };
	image_map["enemy0"] = { 32,32,IMG_Load("../Ryujin_SDL2/dat/img/enemy/0.png") };

	image_map["pb0"] = { 11,55,IMG_Load("../Ryujin_SDL2/dat/img/player/bl_00.png")};
	image_map["pb1"] = { 35,35,IMG_Load("../Ryujin_SDL2/dat/img/player/bl_01.png")};
	player_bullet_image_list.push_back("pb0");
	player_bullet_image_list.push_back("pb1");

	image_map["b0"] = { 76,76,IMG_Load("../Ryujin_SDL2/dat/img/bullet/b0.png") };
	image_map["b1"] = { 22,22,IMG_Load("../Ryujin_SDL2/dat/img/bullet/b1.png") };
	image_map["b2"] = { 10,120,IMG_Load("../Ryujin_SDL2/dat/img/bullet/b2.png") };
	image_map["b3"] = { 19,34,IMG_Load("../Ryujin_SDL2/dat/img/bullet/b3.png") };
	image_map["b4"] = { 38,38,IMG_Load("../Ryujin_SDL2/dat/img/bullet/b4.png") };
	image_map["b5"] = { 14,16,IMG_Load("../Ryujin_SDL2/dat/img/bullet/b5.png") };
	image_map["b6"] = { 14,18,IMG_Load("../Ryujin_SDL2/dat/img/bullet/b6.png") };
	image_map["b7"] = { 16,16,IMG_Load("../Ryujin_SDL2/dat/img/bullet/b7.png") };
	image_map["b8"] = { 12,18,IMG_Load("../Ryujin_SDL2/dat/img/bullet/b8.png") };
	image_map["b9"] = { 13,19,IMG_Load("../Ryujin_SDL2/dat/img/bullet/b9.png") };
	image_map["b10"] = { 8,8,IMG_Load("../Ryujin_SDL2/dat/img/bullet/b10.png") };
	image_map["b11"] = { 35,32,IMG_Load("../Ryujin_SDL2/dat/img/bullet/b11.png") };
	image_map["b12"] = { 12,12,IMG_Load("../Ryujin_SDL2/dat/img/bullet/b12.png") };
	image_map["b13"] = { 22,22,IMG_Load("../Ryujin_SDL2/dat/img/bullet/b13.png") };
	image_map["b14"] = { 6,6,IMG_Load("../Ryujin_SDL2/dat/img/bullet/b14.png") };
	
	bullet_image_list.push_back("b0");
	bullet_image_list.push_back("b1");
	bullet_image_list.push_back("b2");
	bullet_image_list.push_back("b3");
	bullet_image_list.push_back("b4");
	bullet_image_list.push_back("b5");
	bullet_image_list.push_back("b6");
	bullet_image_list.push_back("b7");
	bullet_image_list.push_back("b8");
	bullet_image_list.push_back("b9");
	bullet_image_list.push_back("b10");
	bullet_image_list.push_back("b11");
	bullet_image_list.push_back("b12");
	bullet_image_list.push_back("b13");
	bullet_image_list.push_back("b14");

	Sound::Load(SOUND_DEFAULT, 30, "../Ryujin_SDL2/dat/se/enemy_shot.wav");
	Sound::Load(SOUND_DEFAULT, 50, "..//Ryujin_SDL2/dat/se/cshot.wav");
}
