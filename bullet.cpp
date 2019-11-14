#include "bullet.h"

BULLET::BULLET(string name,int attack, short effect):
	Creature(name + "'s bullet"),
	effect(effect)
{
	this->HP_ = 1;
	this->ATK_ = attack;
	this->ATK_SPD_ = 0;
}

BULLET::~BULLET()
{
	//static auto count = 1;
	////cout << "bullet destruct " << count << endl;
	//count++;
}
