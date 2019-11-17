#include "bullet.h"


int Bullet::hit()
{
	int damage = ATK_;
	die();
	return damage;
}

Bullet::Bullet(string name,int attack, short effect):
	effect(effect)
{
	this->name_ = name;
	this->HP_ = 1;
	this->ATK_ = attack;
	this->ATK_SPD_ = 0;
	this->SPD_ = 20;
}

Bullet::~Bullet()
{
	//static auto count = 1;
	////cout << "bullet destruct " << count << endl;
	//count++;
}
