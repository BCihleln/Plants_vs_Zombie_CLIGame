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
private:
	int DEF_;//看作額外血量，也就是道具的血量
	tool_type tool;

	void Skill();
protected:
	int SPD_;//移動速度 單位：字符寬/秒
	coordinate direction_;//前進方向

	void move(coordinate& position);
	void die()override;
public:
	Zombie();
	~Zombie();

	void change_type(tool_type target);

	//返回當前時隙僵尸的攻擊力，在map中處理被攻擊的對象
	int next(int clock,coordinate& position, bool obstacle);
};
