#include "creature.h"

Creature::Creature(string name):
	name(name),
	HP(50),//��헔�ֵ0~100
	ATK(20),
	ATK_SPD(1),//ATK_SPD���HӋ�㣺1500ms /ATK_SPD
	SPD(0),
	DEF(0)
{
}

//void Creature::move(coordinate& position)
//{
////����λ�����ã�ֱ���޸�λ��
//
////TODO �Д�ǰ���Ƿ����ϵK��
///*
//�е�Ԓ ����attack_flag���r϶����
//�]�е�Ԓ���^�mǰ�M
//*/
//	position = position + coordinate{ -1, 0 };//��ʬ����һ�ַ���
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
//	if (HP > 0)//߀������Ԓ
//	{
//		if (clock % ATK_SPD == 0)
//			attack();
//		if (clock % SPD == 0)
//			move(position);
//	}
//}
