#include "plants.h"

Plant::Plant():Creature("None"),ID(0)
{
}

Plant::~Plant()
{
//#ifdef DEBUG
//	static int count = 0;
//	cout << "destruct plant " << count<< endl;
//	count++;
//#endif
}

void Plant::set_type(const int ID)
{
	this->ID = ID;
	switch (ID)
	{
	case	1://向日葵
		this->name = "Sun Flower";
		this->HP = 25;
		this->ATK = 0;
		this->ATK_SPD = 10;
		break;
	case 2://豌豆射手
		this->name = "Bean Shooter";
		this->HP = 40;
		this->ATK = 25;
		this->ATK_SPD = 50;
		break;
	case 3://堅果墻
		this->name = "Nut Wall";
		this->HP = 100;
		this->DEF = 25;
		break;
	case 4:
		break;
	case 5:
		break;
	default:
		this->ID = 0;
		break;
	}
}

void Plant::attack()
{
	//射擊型植物的攻擊方式是生產一顆子彈
	BULLET tmp(name,this->ATK,0);
	bullets.push(tmp);//TODO 在函數時會析構掉tmp，不知道是否會影響到queue裏的元素，待逐步調試時查證
}