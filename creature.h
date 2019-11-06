#pragma once
#include "basic.h"

class Creature
{
protected:
	int
		HP,
		ATK, ATK_SPD,//ATK Speed 攻速
		SPD,//移動速度
		DEF;//百分比防禦力最高99%
public:
	string name;

	//Creature();
	Creature(string name);
	//~Creature();

	string get_name();

	void injure(int damage);
	void die();
};