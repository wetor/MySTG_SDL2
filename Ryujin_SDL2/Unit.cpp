/*
单位
包括敌人、BOSS、自机等多帧运动动画


*/

#include "pch.h"
#include "Unit.h"



Unit::Unit()
{
	this->unit_type = UNIT_DEFAULT;		//类型
	this->frame = 0;					//帧计数器
	this->frame_num = 0;				//总帧数
	this->frame_now = 0;				//当前动画帧/序号
	this->frame_rect = NULL;		//帧区域(数组，下标为帧数)
	this->surface = NULL;       //图像
	this->texture = NULL;       //图像
	this->mask_texture = NULL;	//遮罩
	this->x = 0;
	this->y = 0;				//坐标
	this->angle = 0;				//角度
	this->w = 0;
	this->h = 0;					//帧宽高
	this->type = "";				//图像类型
	this->range = 0;
	this->scale = 1;				//缩放
	this->draw_angle = 0;
	this->draw_w = 0;
	this->draw_h = 0;
}
void Unit::Load(string type) {
	surface = image_map[type].surface;

	if (image_map[type].texture != NULL) {
		texture = image_map[type].texture;
	}
	else {
#ifdef MUTEX
		SDL_mutexP(loop_lock);			//锁定
#endif
		texture = SDL_CreateTextureFromSurface(renderer, surface);
#ifdef MUTEX
		SDL_mutexV(loop_lock);
#endif
		image_map[type].texture = texture;
	}
	SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
	// ************************************************
	// 创建白色遮罩层
	// https://discourse.libsdl.org/t/how-to-make-a-color-pixel-transparent-sdl2-question/23367/3
	SDL_LockSurface(surface);
	Uint32* pixels = (Uint32*)surface->pixels;
	int pixelCount = surface->h * surface->w;
	Uint32 transparent = SDL_MapRGBA(surface->format, 0xFF, 0xFF, 0xFF, 0xFF); //白色
	Uint32 alphaShift = surface->format->Ashift;
	Uint32 alphaMask = surface->format->Amask;
	for (int i = 0; i < pixelCount; ++i) {
		if (((pixels[i] & alphaMask) >> alphaShift) != 0)
			pixels[i] = transparent;
	}

	if (image_map["mask_"+type].texture != NULL) {
		mask_texture = image_map["mask_" + type].texture;
	}
	else {
#ifdef MUTEX
		SDL_mutexP(loop_lock);			//锁定
#endif
		mask_texture = SDL_CreateTextureFromSurface(renderer, surface);
#ifdef MUTEX
		SDL_mutexV(loop_lock);
#endif
		image_map["mask_" + type].texture = mask_texture;
	}
	//SDL_UpdateTexture(texture, NULL, (unsigned char*)surface->pixels, surface->pitch);
	SDL_free(pixels);
	SDL_UnlockSurface(surface);
	SDL_SetTextureBlendMode(mask_texture, SDL_BLENDMODE_BLEND);
	// ************************************************

	this->type = type;
	this->w = image_map[type].width;
	this->h = image_map[type].height;
}
void Unit::Init(UNIT_TYPE unit_type) {

	this->unit_type = unit_type;
	frame = 0;
	int t_h = surface->h / h;
	int t_w = surface->w / w;
	frame_num = t_h * t_w;
	frame_rect = new SDL_Rect[t_h * t_w];
	frame_now = 0;
	int k = 0;
	for (int i = 0; i < t_h; i++) {
		for (int j = 0; j < t_w; j++) {
			frame_rect[k++] = { j*w, i*h, w, h };
		}
	}
	angle = 0;
}
void Unit::Render(int bright)
{
	if (this->frame < 0) return;			//frame为负数即等待帧数
		
	// 使用renderCopy
	
	//bright_set.brt = (unsigned char)((SDL_GetTicks() / 10) % 255);
	if (bright_set.brt < 255)
	{
		SDL_SetTextureColorMod(texture, bright_set.brt, bright_set.brt, bright_set.brt);
		SDL_SetTextureColorMod(mask_texture, bright_set.brt, bright_set.brt, bright_set.brt);
	}
	SDL_RenderCopyExF(renderer, texture, &frame_rect[frame_now], &draw_rect, draw_angle, &draw_center, SDL_FLIP_NONE);
	if (bright > 0) {
		SDL_SetTextureAlphaMod(mask_texture, bright);
		SDL_RenderCopyExF(renderer, mask_texture, &frame_rect[frame_now], &draw_rect, draw_angle, &draw_center, SDL_FLIP_NONE);

		//SDL_BlendMode SubBlendMode = SDL_ComposeCustomBlendMode(SDL_BLENDFACTOR_SRC_ALPHA, SDL_BLENDFACTOR_ONE, SDL_BLENDOPERATION_ADD, SDL_BLENDFACTOR_ZERO, SDL_BLENDFACTOR_ONE, SDL_BLENDOPERATION_ADD);
		//SDL_SetTextureBlendMode(texture, SubBlendMode);
		//SDL_SetTextureAlphaMod(texture, 255);
	}
	//SDL_RenderCopy(render, texture, &frame_rect[frame_now], temp_rect);


	////使用blitSurface
	//float _w = this->scale * this->w;
	//float _h = this->scale * this->h;
	//SDL_Rect temp_rect = { (int)(x - _w / 2.0 + 0.5) , (int)(y - _h / 2.0 + 0.5),(int)_w, (int)_h };
	//SDL_Point temp_point = { (int)(_w / 2.0),(int)(_h / 2.0) };
	//if (bright > 0) {
	//	SDL_SetSurfaceAlphaMod(surface, bright);
	//	SDL_SetSurfaceBlendMode(surface, SDL_BLENDMODE_BLEND);
	//}
	////bright_set.brt = (unsigned char)((SDL_GetTicks() / 10) % 255);
	//if (bright_set.brt < 255)
	//{
	//	SDL_SetSurfaceColorMod(surface, bright_set.brt, bright_set.brt, bright_set.brt);
	//	SDL_SetSurfaceBlendMode(surface, SDL_BLENDMODE_BLEND);
	//}
	//	
	//SDL_BlitSurface(surface, &frame_rect[frame_now], game_surface, &temp_rect);



	
#ifdef COLLIDER
	
	SDL_FRect temp_rect ={ x - this->range*1.5f  , y - this->range*1.5f ,  this->range * 3.0f, this->range * 3.0f };
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 150);
	SDL_RenderFillRectF(renderer, &temp_rect);
	temp_rect = { x - this->range  , y - this->range ,  this->range * 2.0f, this->range * 2.0f };
	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 150);
	SDL_RenderFillRectF(renderer, &temp_rect);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	
	
#endif
}

void Unit::Update()
{
	frame++;
	draw_w = this->scale * this->w;
	draw_h = this->scale * this->h;
	draw_rect = { x - draw_w / 2.0f + 0.5f , y - draw_h / 2.0f + 0.5f, draw_w, draw_h };
	draw_center = { draw_w / 2.0f, draw_h / 2.0f };
	draw_angle = angle * 180 / PI;
	if (unit_type == UNIT_BULLET || unit_type == UNIT_PLAYER_BULLET)	//需要更改朝向
		draw_angle += 90;

}
void Unit::Free() {
	surface = NULL;
	texture = NULL;
	//delete frame_rect;


}