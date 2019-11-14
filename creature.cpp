#include "creature.h"

Creature::Creature(string name):
	name_(name),
	HP_(50),//��헔�ֵ0~100
	ATK_(20),
	ATK_SPD_(1)//ATK_SPD���HӋ�㣺1500ms /ATK_SPD
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

string Creature::name() const
{
	return name_;
}

void Creature::injure(int damage)
{
	HP_ -= damage;
	if (HP_ < 1)
		die();
}

void Creature::die()
{
	name_ = "died " + name_;
	HP_ = 0;
	ATK_ = 0;
	ATK_SPD_ = 0;
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
