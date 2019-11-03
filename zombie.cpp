#include "zombie.h"

ZOMBIE::ZOMBIE():Creature("zombie")
{
	this->ATK = 50;
	this->ATK_SPD = 10;
	this->HP = 100;
	this->SPD = 10;
	this->DEF = 0;
}

ZOMBIE::~ZOMBIE()
{
}

int ZOMBIE::attack()
{
	return ATK;
}
