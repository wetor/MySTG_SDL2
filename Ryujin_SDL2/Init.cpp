/*
管理者[待改名为Game]
一些控制游戏流程的函数
包括初始化和资源的加载


*/
#include "pch.h"
#include "define.h"
#include "global.h"
#include "Manager.h"

SDL_Rect renderer_rect = { FX,FY,FW, FH };
SDL_Rect window_rect = { 0,0,WINDOW_W,WINDOW_H };

SDL_Window *window = NULL;
SDL_Surface* game_surface = NULL;
SDL_Texture* game_texture = NULL;
SDL_Renderer *renderer = NULL;
TTF_Font *font_default = NULL;
TTF_Font *font_mini = NULL;

SDL_Thread *thread_draw = NULL;
SDL_Thread *thread_emitter = NULL;
SDL_Thread *thread_update = NULL;
SDL_Thread *thread_script = NULL;


map<string, image_t> image_map;
vector<bullet_info_t> bullet_info;
vector<string> player_bullet_image_list;
vector<string> effect_image_list;

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
	//SDL_SetHint(SDL_HINT_RENDER_VSYNC, "1");
	//SDL_SetHint(SDL_HINT_RENDER_DRIVER, "opengl");
	
	//SDL_SetHint(SDL_HINT_RENDER_DIRECT3D_THREADSAFE, "0");

	TTF_Init();

	window = SDL_CreateWindow("Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_W, WINDOW_H, SDL_WINDOW_RESIZABLE);
	if (window == NULL) return false;

	//加载渲染器
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED );
	//游戏画面总的surface
	// SDL_PIXELFORMAT_ARGB8888;
	game_surface = SDL_CreateRGBSurface(SDL_SWSURFACE, WINDOW_W, WINDOW_H, 32, 0x000000ff, 0x0000ff00, 0x00ff0000, 0xff000000);
	game_texture = SDL_CreateTextureFromSurface(renderer, game_surface);


	if (renderer == NULL) return false;
	SDL_RenderSetLogicalSize(renderer, WINDOW_W, WINDOW_H);
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	font_default = TTF_OpenFont("../Ryujin_SDL2/dat/font/font0.ttf", 22);
	font_mini = TTF_OpenFont("../Ryujin_SDL2/dat/font/font0.ttf", 14);
	
	if (font_default == NULL)  return false;


	bright_set.brt = 255;

	//SDL_SetWindowBrightness(window, 1.0);
	//SDL_BlendMode(SDL_BLENDMODE_BLEND);
	return true;
}
void ResourcesInit() {
	image_map.clear();
	player_bullet_image_list.clear();

	image_map["player"] = { 32,48,IMG_Load("../Ryujin_SDL2/dat/img/player/reimu.png") };
	image_map["center"] = { 13,13,IMG_Load("../Ryujin_SDL2/dat/img/player/atari.png") };

	image_map["ball"] = { 40,40,IMG_Load("../Ryujin_SDL2/dat/img/player/ball.png") };
	image_map["hp"] = { 1,6,IMG_Load("../Ryujin_SDL2/dat/img/enemy/hp.png") };
	image_map["hp_boss"] = { 1,6,IMG_Load("../Ryujin_SDL2/dat/img/enemy/hp_boss.png") };

	image_map["enemy0"] = { 32,32,IMG_Load("../Ryujin_SDL2/dat/img/enemy/0.png") };

	image_map["pb0"] = { 11,55,IMG_Load("../Ryujin_SDL2/dat/img/player/bl_00.png")};
	image_map["pb1"] = { 35,35,IMG_Load("../Ryujin_SDL2/dat/img/player/bl_01.png")};
	player_bullet_image_list.push_back("pb0");
	player_bullet_image_list.push_back("pb1");

	image_map["eft0"] = { 140,140,IMG_Load("../Ryujin_SDL2/dat/img/enemy/hit_effect.png") };
	image_map["bom0"] = { 500,500,IMG_Load("../Ryujin_SDL2/dat/img/effect/bom0.png") };
	image_map["bom1"] = { 500,500,IMG_Load("../Ryujin_SDL2/dat/img/effect/bom1.png") };
	image_map["body"] = { 360,480,IMG_Load("../Ryujin_SDL2/dat/img/player/body.png") };
	image_map["bom_title0"] = { 600,60,IMG_Load("../Ryujin_SDL2/dat/img/bullet/bom_title0.png") };
	effect_image_list.push_back("eft0");
	effect_image_list.push_back("bom0");
	effect_image_list.push_back("bom1");
	effect_image_list.push_back("body");
	effect_image_list.push_back("bom_title0");


	image_map["back0"] = { 522,952,IMG_Load("../Ryujin_SDL2/dat/img/back/0/back0.png") };

	image_map["boss"] = { 100,100,IMG_Load("../Ryujin_SDL2/dat/img/player/riria.png") };

	//image_map["b0"] = { 76,76,IMG_Load("../Ryujin_SDL2/dat/img/bullet/b0.png") };
	//image_map["b1"] = { 22,22,IMG_Load("../Ryujin_SDL2/dat/img/bullet/b1.png") };
	//image_map["b2"] = { 10,120,IMG_Load("../Ryujin_SDL2/dat/img/bullet/b2.png") };
	//image_map["b3"] = { 19,34,IMG_Load("../Ryujin_SDL2/dat/img/bullet/b3.png") };
	//image_map["b4"] = { 38,38,IMG_Load("../Ryujin_SDL2/dat/img/bullet/b4.png") };
	//image_map["b5"] = { 14,16,IMG_Load("../Ryujin_SDL2/dat/img/bullet/b5.png") };
	//image_map["b6"] = { 14,18,IMG_Load("../Ryujin_SDL2/dat/img/bullet/b6.png") };
	//image_map["b7"] = { 16,16,IMG_Load("../Ryujin_SDL2/dat/img/bullet/b7.png") };
	//image_map["b8"] = { 12,18,IMG_Load("../Ryujin_SDL2/dat/img/bullet/b8.png") };
	//image_map["b9"] = { 13,19,IMG_Load("../Ryujin_SDL2/dat/img/bullet/b9.png") };
	//image_map["b10"] = { 8,8,IMG_Load("../Ryujin_SDL2/dat/img/bullet/b10.png") };
	//image_map["b11"] = { 35,32,IMG_Load("../Ryujin_SDL2/dat/img/bullet/b11.png") };
	//image_map["b12"] = { 12,12,IMG_Load("../Ryujin_SDL2/dat/img/bullet/b12.png") };
	//image_map["b13"] = { 22,22,IMG_Load("../Ryujin_SDL2/dat/img/bullet/b13.png") };
	//image_map["b14"] = { 6,6,IMG_Load("../Ryujin_SDL2/dat/img/bullet/b14.png") };
	//比如：0号子弹，大小76x76像素，有五种颜色，碰撞范围为17像素

	bullet_info.push_back({ "b0", 76, 76, 5, 17.0 });
	bullet_info.push_back({ "b1", 22, 22, 6, 4.0 });
	bullet_info.push_back({ "b2", 5, 120, 10, 2.5 });
	bullet_info.push_back({ "b3", 19, 34, 5, 2.0 });
	bullet_info.push_back({ "b4", 38, 38, 10, 2.0 });
	bullet_info.push_back({ "b5", 14, 16, 3, 3.5 });
	bullet_info.push_back({ "b6", 14, 18, 3, 2.0 });
	bullet_info.push_back({ "b7", 16, 16, 9, 2.5 });
	bullet_info.push_back({ "b8", 12, 18, 10, 1.5 });
	bullet_info.push_back({ "b9", 13, 19, 3, 2.0 });

	for (int i = 0; i < (int)bullet_info.size(); i++) {
		image_map[bullet_info[i].id] = { bullet_info[i].w, bullet_info[i].h, IMG_Load(("../Ryujin_SDL2/dat/img/bullet/" + bullet_info[i].id + ".png").c_str()) };
	}

	

	//bullet_image_list.push_back("b10");
	//bullet_image_list.push_back("b11");
	//bullet_image_list.push_back("b12");
	//bullet_image_list.push_back("b13");
	//bullet_image_list.push_back("b14");

	Sound::Load(SOUND_TYPE::DEFAULT, 25, "../Ryujin_SDL2/dat/se/enemy_shot.wav");	//0
	Sound::Load(SOUND_TYPE::DEFAULT, 50, "../Ryujin_SDL2/dat/se/cshot.wav");		//1
	Sound::Load(SOUND_TYPE::DEFAULT, 50, "../Ryujin_SDL2/dat/se/hit.wav");		//2
	Sound::Load(SOUND_TYPE::DEFAULT, 50, "../Ryujin_SDL2/dat/se/enemy_death.wav");//3
	Sound::Load(SOUND_TYPE::DEFAULT, 50, "../Ryujin_SDL2/dat/se/char_death.wav");//4
	Sound::Load(SOUND_TYPE::DEFAULT, 50, "../Ryujin_SDL2/dat/se/bom0.wav");//5
	Sound::Load(SOUND_TYPE::DEFAULT, 50, "../Ryujin_SDL2/dat/se/bom1.wav");//6

}
