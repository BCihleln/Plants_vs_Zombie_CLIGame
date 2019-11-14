#pragma once
#include "basic.h"
#include "creature.h"


enum class tool_type
{
	None,
	Flag,
	Barrel, Bucket,
	Newspaper,
	Dancer_King
};

//行走攻擊分開執行，每時隙只能執行其中一個
class Zombie:public Creature
{
	int
		SPD_,//移動速度 單位：字符寬/秒
		DEF_;//是額外血量，也就是道具的血量
	coordinate direction;//前進方向

	tool_type tool;

	void Skill();
	void move(coordinate& position);
public:
	Zombie();
	~Zombie();

	void change_type(tool_type target);

	//返回當前時隙僵尸的攻擊力，在map中處理被攻擊的對象
	int next(int clock,coordinate& position, bool obstacle);
};
