#include "zombie.h"

ZOMBIE::ZOMBIE():Creature("zombie")
{
	this->ATK = 50;
	this->ATK_SPD = 10;
	this->HP = 100;
	this->SPD = 10;
	this->DEF = 0;
	attack_flag = false;
}

ZOMBIE::~ZOMBIE()
{
}

void ZOMBIE::attack()
{
}

void ZOMBIE::move(coordinate& position)
{	//傳入位置引用，直接修改位置

	//TODO 判斷前面是否有障礙物
	/*
	有的話 更改attack_flag下個時隙攻擊
	沒有的話，繼續前進
	*/

	if(attack_flag==false)
		position = position+coordinate{-1, 0};//僵尸靠近一字符寬

}

void ZOMBIE::next(int clock, coordinate& position)
{
	if (HP > 0)//還活著的話
	{
		if (clock % ATK_SPD == 0)
			attack();

		if (clock % SPD == 0)
			move(position);
	}
}
