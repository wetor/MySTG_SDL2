#include "pch.h"
#include "Boss.h"
#include "Manager.h"

namespace NspBoss {
	Boss::Boss() : Unit()
	{
	}
	void Boss::AddEmitter(int emitter_id)
	{
		this->emitter_id[emitter_id] = 1;
		this->emitter_state[emitter_id] = EMITTER_STATE::DEFAULT;
	}
	void Boss::DestroyEmitter(int emitter_id)
	{
		this->emitter_id[emitter_id] = 0;
	}
	void Boss::Init(int num)
	{
		Unit::Load("boss");
		Unit::Init(UNIT_TYPE::BOSS);
		if (num == 0) {//中路Boss开始时的情况
			NspEmitter::EmitterClear(); // 后续会一起删除子弹，所以不需要在这里清除子弹
			NspEnemy::EnemyClear();
			NspBullet::BulletClear();
			x = FX + FW / 2.0f;//设置Boss的初始坐标
			y = -30;
			knd = 0;//弹幕的种类

		}
		flag = true;
		hagoromo = 0;//是否扇状扩散的flag
		endtime = 99 * 60;//剩余时间
		state = BOSS_STATE::WAITING;//设置状态为待机中
		this->frame = 0;
		graph_flag = 0;//恢复绘制flag
		wtime = 0;//初始化待机时间
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
	void Boss::Render()
	{
		if (!flag)
			return;
		Unit::Render();
	}
	void Boss::Update()
	{
		if (!flag)
			return;
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
		
		Unit::Update();
	}
}