#pragma once
#include "basic.h"
//#include "map.h"

class Creature
{
protected:
	string name_;
	int
		HP_,
		ATK_,
		ATK_SPD_;//ATK Speed ¹¥ËÙ †ÎÎ»£º´Î/Ãë
	virtual void die()=0;
public:

	//Creature();
	Creature(string name);
	//~Creature();

	//string get_name();

	//virtual void move(coordinate& position);

	//virtual void attack();
	
	string name()const;
	void injure(int damage);

	//virtual void next(int clock,coordinate& position);
};