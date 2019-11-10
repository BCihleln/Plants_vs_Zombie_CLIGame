#pragma once
#include "basic.h"
//#include "map.h"

class Creature
{
protected:
	string name_;
	int
		HP_,
		ATK_, ATK_SPD_,//ATK Speed 攻速 單位：次/秒
		SPD_,//移動速度 單位：字符寬/秒
		DEF_;//百分比防禦力最高99%

	//coordinate ATK_direction;
	coordinate direction;//前進方向
public:

	//Creature();
	Creature(string name);
	//~Creature();

	//string get_name();

	//virtual void move(coordinate& position);

	//virtual void attack();

	//用於子彈、僵尸前進
	//bool check_obstacle(const mapCell& front);

	void injure(int damage);
	void die();

	//virtual void next(int clock,coordinate& position);
};