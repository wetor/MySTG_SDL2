#pragma once
#include "struct.h"
#include "define.h"
#include <deque>



class Emitter
{
public:
	Emitter();
	~Emitter();

	bool isExist() { return (flag == -1) ? false : true; };
	int AddBulletID(int id);
	void Init(int enemy_id);
	void Update();
public:
	//flag、种类、计数器、发射的敌人的编号
	int  enemy_id, flag, knd, frame;
	//基本角度、基本速度
	double x, y, base_angle[1], base_spd[1];
	
	int* bullet_id_list;

};


void emitter_bullet_H000(Emitter *_this);
void emitter_bullet_H001(Emitter *_this);
void emitter_bullet_H002(Emitter *_this);
void emitter_bullet_H003(Emitter *_this);
void emitter_bullet_H004(Emitter *_this);
void emitter_bullet_H005(Emitter *_this);
void emitter_bullet_H006(Emitter *_this);
