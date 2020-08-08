#include "pch.h"
#include "Boss.h"
#include "Manager.h"

namespace NspBoss {
	Boss::Boss() : Unit()
	{
		bg_effect = new NspEffect::BossEffect();
	}
	void Boss::AddEmitter(int emitter_id)
	{
		this->emitter_id[emitter_id] = true;
		this->emitter_state[emitter_id] = EMITTER_STATE::DEFAULT;
	}
	void Boss::DestroyEmitter(int emitter_id)
	{
		this->emitter_id[emitter_id] = false;
	}
	void Boss::Death()
	{
		flag = false;
		for (int i = 0; i < EMITTER_MAX; i++) {
			if (emitter_id[i]) {
				emitter_state[i] = EMITTER_STATE::CLEAR;
				emitter_id[i] = false;
			}
		}
		bg_effect->Clear();
	}
	void Boss::Init(boss_t _boss_data) 
	{
		Unit::Load("boss");
		Unit::Init(UNIT_TYPE::BOSS);
		if(hp_surface == NULL)
			hp_surface = SDL_CreateRGBSurface(SDL_SWSURFACE, FW, 6, 32, 0x000000ff, 0x0000ff00, 0x00ff0000, 0xff000000);
		if (hp_texture == NULL) {
			SDL_Rect temp_size = { 0 , 0 ,1, 6 };
			SDL_Rect temp_rect = { 0 , 0 ,1, 6 };
			for (int i = 0; i < FW; i++) {
				temp_rect.x = i;
				SDL_BlitSurface(image_map["hp_boss"].surface, &temp_size, hp_surface, &temp_rect);
			}
			hp_texture = SDL_CreateTextureFromSurface(renderer, hp_surface);
		}

		
		sc_num = _boss_data.sc_num;

		sc_enter = _boss_data.sc_enter;
		sc_hp = _boss_data.sc_hp;
		sc_knd = _boss_data.sc_knd;
		sc_bg = _boss_data.sc_bg;

		sc_index = -1;

		range = 40.0f;

		hagoromo = _boss_data.hagoromo;//是否扇状扩散的flag
		endtime = _boss_data.endtime;//剩余时间

		graph_flag = _boss_data.graph_flag;//恢复绘制flag
		wtime = _boss_data.wtime;//初始化待机时间

		x = _boss_data.x;//设置Boss的初始坐标
		y = _boss_data.y;

		//knd = 0;//弹幕的种类
	}
	void Boss::Enter(int num)
	{
		Death();
		if (num >= sc_num) {
			LogA("Boss死亡");
			return;
		}
		LogA("Boss出现 弹幕 %d", num);
		sc_index = num;
		if (sc_index == 0) {//中路Boss开始时的情况
			//NspEmitter::EmitterClear(); // 后续会一起删除子弹，所以不需要在这里清除子弹
			NspEnemy::EnemyClear(); // enemy.clear -> emitter.clear -> bullet.clear
			//NspBullet::BulletClear();
		}
		hp = sc_hp[sc_index];
		hp_max = hp;

		flag = true;
		state = BOSS_STATE::WAITING;//设置状态为待机中
		this->frame = 0;
		bg_effect->Init();

		input_phy(60);//附加上60次计数在物理计算中回到固定位置
	}
	//进行物理计算的登录（在指定时间t内回到固定位置）
	void Boss::input_phy(int t) {//t=附加在移动上的时间
		float ymax_x, ymax_y; 
		if (t == 0)
			t = 1;
		phy.flag = 1;//登录有效
		phy.cnt = 0;//计数器初始化
		phy.set_t = t;//设置附加移动时间
		ymax_x = x - BOSS_POS_X;//想要移动的水平距离
		phy.v0x = 2 * ymax_x / t;//水平分量的初速度
		phy.ax = 2 * ymax_x / (t * t);//水平分量的加速度
		phy.prex = x;//初始x坐标
		ymax_y = y - BOSS_POS_Y;//想要移动的竖直距离
		phy.v0y = 2 * ymax_y / t;//竖直分量的初速度
		phy.ay = 2 * ymax_y / (t * t);//数值分量的加速度
		phy.prey = y;//初始y坐标
	}
	//进行与某点的指定距离的物理计算的登录（在指定时间t内回到固定位置）
	void Boss::input_phy_pos(float x1, float y1, int t)
	{
		float ymax_x, ymax_y;
		if (t == 0)t = 1;
		phy.flag = 1;//登录有效
		phy.cnt = 0;//计时器初始化
		phy.set_t = t;//设置移动附加时间
		ymax_x = x - x1;//想要移动的水平距离
		phy.v0x = 2 * ymax_x / t;//水平分量的初速度
		phy.ax = 2 * ymax_x / (t * t);//水平分量的加速度
		phy.prex = x;//初始x坐标
		ymax_y = y - y1;//想要移动的水平距离
		phy.v0y = 2 * ymax_y / t;//水平分量的初速度
		phy.ay = 2 * ymax_y / (t * t);//水平分量的加速度
		phy.prey = y;//初始y坐标
	}
	int Boss::move_boss_pos(float x1, float y1, float x2, float y2, float dist, int t)
	{
		int i = 0;
		double t_x, t_y, angle;
		for (i = 0; i < 1000; i++) {
			t_x = x, t_y = y;//设置当前Boss的位置
			angle = NspEffect::rang(PI);//適当地决定前进方向
			t_x += cos(angle) * dist;//向着那个地方移动
			t_y += sin(angle) * dist;
			if (x1 <= t_x && t_x <= x2 && y1 <= t_y && t_y <= y2) {//如果那个点在移动可能的范围内的话
				input_phy_pos(t_x, t_y, t);
				return 0;
			}
		}
		return -1;//1000如果1000次尝试都不能的话就返回错误
	}
	void Boss::Render()
	{

		Unit::Render();
		static SDL_Rect hp_size = { 0 , 0, FW, 6 };
		SDL_FRect temp_rect = { 5.0f + FX + dn.x , 2.0f + FY + dn.y , FW * 0.98f * hp / hp_max, 6.0f };
		SDL_RenderCopyF(renderer, hp_texture, &hp_size, &temp_rect);
		//for (int i = 0; i < FW * 0.98f * hp / hp_max; i++) {
		//	//temp_rect.x = 3 + FX + i + dn.x;
		//	//temp_rect.y = 2 + FY + dn.y;
		//	temp_rect.x = 3 + i;
		//	if (sc_bg[sc_index] == 1) {
		//		SDL_BlitSurface(image_map["hp_boss"].surface, &hp_rect, hp_surface, &temp_rect);
		//		//SDL_RenderCopy(renderer, image_map["hp_boss"].texture, &hp_rect, &temp_rect);
		//	}
		//	else
		//	{
		//		SDL_BlitSurface(image_map["hp"].surface, &hp_rect, hp_surface, &temp_rect);
		//		//SDL_RenderCopy(renderer, image_map["hp"].texture, &hp_rect, &temp_rect);
		//	}
		//}

	}
	void Boss::Update()
	{
		static float s_x = 0, s_y = 0;
		x = s_x;
		y = s_y;
		if (state == BOSS_STATE::SHOOTING) {//如果在弹幕中体力为0的话
			if (endtime <= 0) { //boss结束
				LogA("Boss逃走");
				Death();
				return;
			}
			else if (hp <= 0 || this->frame == get_enter(sc_index+1)) {
				// 当前血量为零 或已经到达下一条生命出现的时间
				bg_effect->Clear();
				Enter(sc_index + 1);//进入下一次弹幕
				return;
			}
		}

		if (this->phy.flag == 1) {//如果物理移动计算有效
			//calc_phy();//进行物理计算
			float t = phy.cnt;
			x = phy.prex - ((phy.v0x * t) - 0.5f * phy.ax * t * t);//计算当前应当所在的x坐标
			y = phy.prey - ((phy.v0y * t) - 0.5f * phy.ay * t * t);//计算当前应当所在的y坐标
			phy.cnt++;
			if (phy.cnt >= phy.set_t)//如果超过附加移动的时间的话
				phy.flag = 0;//オフ 设置移动为无效
		}
		if (this->state == BOSS_STATE::WAITING) {//弹幕之间的待机时间
			//waitandenter();
			int t = 50;
			
			wtime++;
			if (wtime > t) { //如果待机140次计数的话设置弹幕
				wtime = 0;//待机时间0
				frame_shot = 0;
				state = BOSS_STATE::SHOOTING;//设置为弹幕中的状态
				hp = 5000;//HP设定
				hp_max = hp;
				//enter_boss_shot();
			}
		}
		if (this->state == BOSS_STATE::SHOOTING) {//如果在弹幕中
			if (this->frame_shot  == 0) {
				AddEmitter(NspEmitter::EmitterEnter(-1, true));
			}
			frame_shot++;
			//boss_shot_bullet[boss.knd]();//进入弹幕函数
			//boss_shot_calc();//计算弹幕
		}
		this->dx = x;
		this->dy = y + sin(PI2 / 130 * (frame % 130)) * 10;
		s_x = x;
		s_y = y;
		x = dx;
		y = dy;
		endtime--;
		for (int i = 0; i < EMITTER_MAX; i++) {
			if (emitter_id[i]) {
				emitter[i].x = x;
				emitter[i].y = y;
			}
		}
		bg_effect->Update();
		Unit::Update();
		
	}
}