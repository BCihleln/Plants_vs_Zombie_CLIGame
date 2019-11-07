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
	if (HP > 0)//߀������Ԓ
	{
		if (clock % ATK_SPD == 0)
			attack();

		if (clock % SPD == 0)
			move(position);
	}
}
