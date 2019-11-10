#include "zombie.h"

ZOMBIE::ZOMBIE():Creature("zombie")
{
	this->ATK_ = 50;
	this->ATK_SPD_ = 10;
	this->HP_ = 100;
	this->SPD_ = 10;
	this->DEF_ = 0;
	attack_flag = false;
}

ZOMBIE::~ZOMBIE()
{
}

void ZOMBIE::attack()
{
}

void ZOMBIE::move(coordinate& position)
{	//����λ�����ã�ֱ���޸�λ��

	//TODO �Д�ǰ���Ƿ����ϵK��
	/*
	�е�Ԓ ����attack_flag���r϶����
	�]�е�Ԓ���^�mǰ�M
	*/

	if(attack_flag==false)
		position = position+coordinate{-1, 0};//��ʬ����һ�ַ���

}

void ZOMBIE::next(int clock, coordinate& position)
{
	if (HP_ > 0)//߀������Ԓ
	{
		if (attack_flag && clock % ATK_SPD_ == 0)
			attack();

		if (!attack_flag && clock % SPD_ == 0)
			move(position);
	}
}
