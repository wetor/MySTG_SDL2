#include "pch.h"
#include "Emitter.h"
#include "Manager.h"


namespace NspEmitter {
	float bossatan2() {//自机和敌人所成的夹角
		return atan2(player->y - boss->y, player->x - boss->x);
	}
	void boss_shot_bulletH000(Emitter* _this) {
#define TM000 120
        int i, k, t = (boss->frame_shot - 1) % TM000;
		int bullet_id = 0;
		float angle;
		if (t < 60 && t % 10 == 0) {
			angle = bossatan2();
			for (i = 0; i < 30; i++) {
				bullet_t temp;

				temp.col = 0;
				temp.x = _this->x;
				temp.y = _this->y;
				temp.knd = 8;
				temp.angle = angle + PI2 / 30 * i;
				temp.flag = 1;
				temp.cnt = 0;
				temp.spd = 3;
				bullet_id = NspBullet::BulletEnter(&temp);
				_this->AddBulletID(bullet_id);
			}
		}
		//Sound::PlayMusic(0);
		//for (i = 0; i < BOSS_BULLET_MAX; i++) {
		//	if (boss_shot.bullet[i].flag > 0) {

		//	}
		//}
	}

    //沉默的圣奈
    void boss_shot_bulletH001(Emitter* _this) {
#define TM001 60
        int i, k, t = (boss->frame_shot - 1) % TM001, t2 = (boss->frame_shot - 1);
        static int cnum;
        int bullet_id = 0;
        float angle;
        if (t2 == 0)//最开始的初始化
            cnum = 0;
        if (t == 0) {//每1次弹幕最开始的初始化
            boss->base_angle[0] = bossatan2();//自机与Boss的角度
            if (cnum % 4 == 3) {// 4次弹幕移动一次
                boss->move_boss_pos(FX + 40, FY + 30, FMX - 40, FX + 120, 60, 60);
            }
        }
        //1次弹幕的最开始是自机狙，到了一半之后从自机狙错开
        if (t == TM001 / 2 - 1)
            boss->base_angle[0] += PI2 / 20 / 2;
        //1次弹幕发射10次圆形子弹
        if (t % (TM001 / 10) == 0) {
            angle = bossatan2();//自机-Boss之间的角度
            for (i = 0; i < 20; i++) {//20个
                bullet_t temp;

                temp.col = 4;
                temp.x = _this->x;
                temp.y = _this->y;
                temp.knd = 8;
                //从基本角度开始旋转20次并发射
                temp.angle = boss->base_angle[0] + PI2 / 20 * i;
                temp.flag = 1;
                temp.cnt = 0;
                temp.spd = 2.7f;
                bullet_id = NspBullet::BulletEnter(&temp);
                _this->AddBulletID(bullet_id);
                Sound::PlayMusic(0);
            }
        }
        //4次计数掉落一次的子弹的登录
        if (t % 4 == 0) {
            bullet_t temp;

            temp.col = 0;
            temp.x = FX + rand() % FW;
            temp.y = FY + rand() % 200;
            temp.knd = 8;
            //从基本角度开始旋转20次并发射
            temp.angle = PI / 2;
            temp.flag = 1;
            temp.cnt = 0;
            temp.spd = 1 + rang(0.5f);
            bullet_id = NspBullet::BulletEnter(&temp);
            _this->AddBulletID(bullet_id);
            Sound::PlayMusic(0);

        }
        if (t == TM001 - 1)
            cnum++;
    }

    //完美冻结
    void boss_shot_bulletH002(Emitter* _this) {
#define TM002 650
        int i, k, t = (boss->frame_shot - 1) % TM002;
        float angle;
        int bullet_id = 0;
        if (t == 0 || t == 210) {
            //在40<x<FMX-40  50<y<150的范围内80次计数中移动到100单位远的地方
            boss->move_boss_pos(FX + 40, FY + 50, FMX - 40, FY + 150, 100, 80);
        }
        //最开始的随机发射
        if (t < 180) {
            for (i = 0; i < 2; i++) {//1次计数发射2次
                bullet_t temp;

                temp.col = rand()%7;//随机像是7种颜色
                temp.x = _this->x;
                temp.y = _this->y;
                temp.knd = 7;
                temp.angle = rang(PI2 / 20) + PI2 / 10 * t;
                temp.flag = 1;
                temp.cnt = 0;
                temp.spd = 3.2f + rang(2.1f);
                temp.state = 0;//子弹的状态
                temp.rotate = 1;//决定子弹是否旋转的flag
                bullet_id = NspBullet::BulletEnter(&temp);
                _this->AddBulletID(bullet_id);
            }
            if (t % 10 == 0)
                Sound::PlayMusic(0);
        }
        //根据自机的位置往8个方向发射
        if (210 < t && t < 270 && t % 3 == 0) {
            angle = bossatan2();
            for (i = 0; i < 8; i++) {

                bullet_t temp;

                temp.col = 0;
                temp.x = _this->x;
                temp.y = _this->y;
                temp.knd = 7;
                //以自机与Boos所成的夹角为基准往8个方向发射
                temp.angle = angle - PI / 2 * 0.8 + PI * 0.8 / 7 * i + rang(PI / 180);
                temp.flag = 1;
                temp.cnt = 0;
                temp.spd = 3.0f + rang(0.3f);
                temp.state = 2;//子弹的状态
                temp.rotate = 1;//决定子弹是否旋转的flag
                bullet_id = NspBullet::BulletEnter(&temp);
                _this->AddBulletID(bullet_id);
            }
            if (t % 10 == 0)
                Sound::PlayMusic(0);
        }
        
        for (i = 0; i < BULLET_MAX; i++) {
            if (_this->bullet_id[i]) {
                //t在190的时候将所有的子弹都停止下来，然后变白色，重置计数器
                if (bullet[i].state == 0) {
                    if (t == 190) {
                        bullet[i].rotate = 0;//停止子弹的旋转
                        bullet[i].spd = 0;
                        bullet[i].frame_now = 9;
                        bullet[i].frame = 0;
                        bullet[i].state = 1;//将状态设置为1
                    }
                }
                //开始往随机方向移动
                if (bullet[i].state == 1) {
                    if (bullet[i].frame == 200) {
                        bullet[i].angle = rang(PI);//全方向随机
                        bullet[i].rotate = 1;//设置旋转flag为有效
                    }
                    if (bullet[i].frame > 200)
                        bullet[i].spd += 0.01;//逐渐加速
                }
            }
        }
    }

    //恋之迷路
    void boss_shot_bulletH003(Emitter* _this) {
#define TM003 600
#define DF003 20 
    
        int i, j, k, t = (boss->frame_shot - 1) % TM003, t2 = (boss->frame_shot - 1);
        static int tcnt, cnt, cnum;
        float angle;
        int bullet_id = 0;
        if (t2 == 0) {
            //在40<x<FMX-40  50<y<150的范围内80次计数中移动到100单位外的位置
            boss->input_phy_pos(FX + FW/2, FY + FH/2, 50);
            cnum = 0;
        }
        if (t == 0) {
            boss->base_angle[0] = bossatan2();
            cnt = 0;
            tcnt = 2;
        }
        if (t < 540 && t % 3) {
            angle = bossatan2();
            if (tcnt - 2 == cnt || tcnt - 1 == cnt) {
                if (tcnt - 1 == cnt) {
                    boss->base_angle[1] = boss->base_angle[0] + PI2 / DF003 * cnt * (cnum ? -1 : 1) - PI2 / (DF003 * 6) * 3;
                    tcnt += DF003 - 2;
                }
            }
            else {
                for (i = 0; i < 6; i++) {
                    bullet_t temp;

                    temp.col = cnum ? 1 : 4;
                    temp.x = _this->x;
                    temp.y = _this->y;
                    temp.knd = 8;
                    temp.angle = boss->base_angle[0] + PI2 / DF003 * cnt * (cnum ? -1 : 1) + PI2 / (DF003 * 6) * i * (cnum ? -1 : 1);
                    temp.flag = 1;
                    temp.cnt = 0;
                    temp.spd = 2;
                    bullet_id = NspBullet::BulletEnter(&temp);
                    _this->AddBulletID(bullet_id);
                    Sound::PlayMusic(0);
                }
            }
            cnt++;
        }
        if (40 < t && t < 540 && t % 30 == 0) {
            for (j = 0; j < 3; j++) {
                angle = boss->base_angle[1] - PI2 / 36 * 4;
                for (i = 0; i < 27; i++) {
                    bullet_t temp;

                    temp.col = cnum ? 6 : 0;
                    temp.x = _this->x;
                    temp.y = _this->y;
                    temp.knd = 7;
                    temp.angle = angle;
                    temp.flag = 1;
                    temp.cnt = 0;
                    temp.spd = 4 - 1.6f / 3 * j;
                    bullet_id = NspBullet::BulletEnter(&temp);
                    _this->AddBulletID(bullet_id);
                    Sound::PlayMusic(0);

                    angle -= PI2 / 36;
                }
            }
        }
        //    for(i=0;i<BOSS_BULLET_MAX;i++){
        //        if(boss_shot.bullet[i].flag>0){
        //
        //        }
        //    }
        if (t == TM003 - 1)
            cnum++;
    }

    //小小青蛙不畏风雨
    void boss_shot_bulletH004(Emitter* _this) {
#define TM004 200
        int i, j, k, n, t = (boss->frame_shot - 1) % TM004, t2 = (boss->frame_shot - 1);
        static int tm;
        float angle;
        int bullet_id = 0;
        //周期的最开始设置tm
        if (t == 0)
            tm = 190 + rang(30);
        angle = PI * 1.5f + PI / 6 * sin(PI2 / tm * t2);
        //每4次计数往8路射出子弹
        if (t2 % 4 == 0) {
            for (n = 0; n < 8; n++) {

                bullet_t temp;
                temp.state = 0;
                temp.col = 0;
                temp.x = _this->x;
                temp.y = _this->y;
                temp.vx = cos(angle - PI / 8 * 4 + PI / 8 * n + PI / 16) * 3;
                temp.vy = sin(angle - PI / 8 * 4 + PI / 8 * n + PI / 16) * 3;
                temp.knd = 4;
                temp.angle = 0;
                temp.flag = 1;
                temp.cnt = 0;
                temp.eff_detail = 1;
                temp.spd = 0;
                bullet_id = NspBullet::BulletEnter(&temp);
                _this->AddBulletID(bullet_id);
                
            }
            Sound::PlayMusic(0);
        }
        if (t % 1 == 0 && t2 > 80) {
            int num = 1;
            if (t % 2)
                num = 2;
            for (n = 0; n < num; n++) {
                angle = PI * 1.5f - PI / 2 + PI / 12 * (t2 % 13) + rang(PI / 15);
                bullet_t temp;
                temp.state = 1;
                temp.col = 4;
                temp.x = _this->x;
                temp.y = _this->y;
                temp.vx = cos(angle) * 1.4f * 1.2f;
                temp.vy = sin(angle) * 1.4f;
                temp.knd = 8;
                temp.angle = 0;
                temp.flag = 1;
                temp.cnt = 0;
                temp.eff_detail = 0;
                temp.spd = 0;
                bullet_id = NspBullet::BulletEnter(&temp);
                _this->AddBulletID(bullet_id);
            }
            Sound::PlayMusic(0); // 7
        }
        for (i = 0; i < BULLET_MAX; i++) {
            if (_this->bullet_id[i]) {
                if (bullet[i].state == 0) {
                    if (bullet[i].frame < 150)
                        bullet[i].vy += 0.03;
                    //bullet[i].x += bullet[i].vx;
                    //bullet[i].y += bullet[i].vy;
                }
                if (bullet[i].state == 1) {
                    if (bullet[i].frame < 160)
                        bullet[i].vy += 0.03;
                    //bullet[i].x += bullet[i].vx;
                    //bullet[i].y += bullet[i].vy;
                    //bullet[i].angle = atan2(bullet[i].vy, bullet[i].vx);
                }
            }
        }

    }
}