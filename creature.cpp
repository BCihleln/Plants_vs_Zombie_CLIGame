#include "creature.h"

Creature::Creature(string name):
	name_(name),
	HP_(50),//各項數值0~100
	ATK_(20),
	ATK_SPD_(1),//ATK_SPD實際計算：1500ms /ATK_SPD
	SPD_(0),
	DEF_(0)
{
}

//void Creature::move(coordinate& position)
//{
////傳入位置引用，直接修改位置
//
////TODO 判斷前面是否有障礙物
///*
//有的話 更改attack_flag下個時隙攻擊
//沒有的話，繼續前進
//*/
//	position = position + coordinate{ -1, 0 };//僵尸靠近一字符寬
//}
//
//void Creature::attack()
//{
//}

//string Creature::get_name()
//{
//	return name;
//}

void Creature::injure(int damage)
{
	HP_ -= (damage * (DEF_-1) / 100);
	if (HP_ < 1)
		die();
}

void Creature::die()
{
	name_ = "died " + name_;
	HP_ = 0;
	ATK_ = 0;
	ATK_SPD_ = 0;
	SPD_ = 0;
	DEF_ = 0;
}

//void Creature::next(int clock, coordinate& position)
//{
//	if (HP > 0)//還活著的話
//	{
//		if (clock % ATK_SPD == 0)
//			attack();
//		if (clock % SPD == 0)
//			move(position);
//	}
//}
