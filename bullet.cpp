#include "bullet.h"

BULLET::BULLET(string name,int attack, short effect):
	Creature(name + "'s bullet"),
	effect(effect)
{
	this->ATK = attack;
	this->ATK_SPD = 0;
	this->DEF = 0;
	this->SPD = 1;
	this->HP = 1;
}

BULLET::~BULLET()
{
#ifdef DEBUG
	static auto count = 1;
	cout << "bullet destruct " << count << endl;
	count++;
#endif // DEBUG
}
