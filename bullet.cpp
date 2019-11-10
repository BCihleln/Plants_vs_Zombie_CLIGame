#include "bullet.h"

BULLET::BULLET(string name,int attack, short effect):
	Creature(name + "'s bullet"),
	effect(effect)
{
	this->ATK_ = attack;
	this->ATK_SPD_ = 0;
	this->DEF_ = 0;
	this->SPD_ = 1;
	this->HP_ = 1;
}

BULLET::~BULLET()
{
#ifdef DEBUG
	static auto count = 1;
	cout << "bullet destruct " << count << endl;
	count++;
#endif // DEBUG
}
