#pragma once
#include "basic.h"
//#include "map.h"

class Creature
{
protected:
	int
		HP,
		ATK, ATK_SPD,//ATK Speed 攻速
		SPD,//移動速度
		DEF;//百分比防禦力最高99%

	//coordinate ATK_direction;
	coordinate direction;//前進方向
public:
	string name;

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