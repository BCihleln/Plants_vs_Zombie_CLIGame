#include "creature.h"

Creature::Creature(string name):
	name(name),
	HP(50),//各項數值0~100
	ATK(20),
	ATK_SPD(1),//ATK_SPD實際計算：1500ms /ATK_SPD
	SPD(0),
	DEF(0)
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
	HP -= (damage * (DEF-1) / 100);
	if (HP < 1)
		die();
}

void Creature::die()
{
	name = "died " + name;
	HP = 0;
	ATK = 0;
	ATK_SPD = 0;
	SPD = 0;
	DEF = 0;
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
