#include "zombie.h"

Zombie::Zombie():
	Creature("Zombie"),
	direction(coordinate{-1,0})
{
	this->ATK_ = 20;
	this->ATK_SPD_ = 10;
	this->HP_ = 100;
	this->SPD_ = 10;
	this->DEF_ = 0;
}

Zombie::~Zombie()
{
}

void Zombie::move(coordinate& position)
{	//����λ�����ã�ֱ���޸�λ��
	position = position+coordinate{-1, 0};//��ʬ����һ�ַ���
}

void Zombie::die()
{
	name_ = "None";
	HP_ = 0;
	ATK_ = 0;
	ATK_SPD_ = 0;
	SPD_ = 0;
	DEF_ = 0;
	tool = tool_type::None;
	direction = coordinate{ 0,0 };
}

//���خ�ǰ�r϶��ʬ�Ĺ�����
int Zombie::next(int clock, coordinate& position, bool obstacle)
{
	if (HP_ > 0)//߀������Ԓ
	{
		if (obstacle && clock % ATK_SPD_ == 0)
			return ATK_;

		if (!obstacle && clock % SPD_ == 0)
			move(position);
	}
	return 0;
}

void Zombie::change_type(tool_type target)
{
	switch (target)
	{
	case tool_type::None:
		if (tool == tool_type::Newspaper)//�G��newspaper�󣬿�
		{
			ATK_ += 30;
			ATK_SPD_ += 20;
			SPD_ += 10;
		}
		DEF_ = 0;
		break;
	case tool_type::Flag:
		name_ = "Flag";
		break;
	case tool_type::Barrel:
		name_ = "Barrel";
		DEF_ = 50;
		break;
	case tool_type::Bucket:
		name_ = "Bucket";
		DEF_ = 100;
		break;
	case tool_type::Newspaper:
		name_ = "Newspaper";
		break;
	case tool_type::Dancer_King:
		name_ = "Dancer King";
		break;
	}
	tool = target;
	name_ += " Zombie";
}