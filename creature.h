#pragma once
#include "basic.h"

class Creature
{
	
public:
	string name;
	int
		HP,
		ATK,ATK_SPD,//ATK Speed 攻速
		SPD,//移動速度
		DEF;//百分比防禦力最高99%

	//Creature();
	Creature(string name);
	//~Creature();

	void injure(int damage);
	void die();
};