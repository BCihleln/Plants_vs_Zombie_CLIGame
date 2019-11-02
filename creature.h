#pragma once
#include "basic.h"

class Creature
{
	
public:
	string name;
	int
		HP,
		ATK,ATK_SPD,//ATK Speed ¹¥ËÙ
		SPD,//ÒÆ„ÓËÙ¶È
		DEF;

	Creature();
	Creature(string name);
	//~Creature();

	void injure(int damage);
	void die();
};