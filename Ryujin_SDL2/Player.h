#pragma once
#include "Unit.h"

class Player :
	public Unit
{
public:
	Player();
	void Init();
	void Draw() { Unit::Draw(); };
	void Update() ;
private:
	
	int flag;       //flag
	
	int power;      //power
	int point;      //点数
	int score;      //分数
	int num;        //残机数
	int mutekicnt;  //无敌状态与计数变量
	int shot_mode;  //射击模式
	int money;      //金钱
	bool slow;       //是否缓慢移动
	
	
};

