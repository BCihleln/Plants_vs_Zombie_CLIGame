#include "plants.h"

Plant::Plant():Creature("None"),ID(None)
{
	this->cost = 0;
}

Plant::~Plant()
{
//#ifdef DEBUG
//	static int count = 0;
//	cout << "destruct plant " << count<< endl;
//	count++;
//#endif
}

void Plant::set_type(const plant_list ID)
{
	if(this->ID==None)//只能被設置一次
	{
		this->ID = ID;
		switch (ID)
		{
		case	Sun_Flower:
			this->name = "Sun Flower";
			this->HP = 25;
			this->ATK = 0;
			this->ATK_SPD = 10;
			return;
		case Bean_Shooter://豌豆射手
			this->name = "Bean Shooter";
			this->HP = 40;
			this->ATK = 25;
			this->ATK_SPD = 50;
			return;
		case Nut_Wall://堅果墻
			this->name = "Nut Wall";
			this->HP = 100;
			this->DEF = 25;
			return;
		case 4:
			return;
		case 5:
			return;
		default:
			this->ID = None;
			return;
		}
	}
}

void Plant::clean()
{
	ID = None;

}

int Plant::get_cost() const
{
	return this->cost;
}

int Plant::get_cool_time() const
{
	return this->cool_time;
}

void Plant::attack()
{
	//射擊型植物的攻擊方式是生產一顆子彈
	BULLET tmp(name,this->ATK,0);
	bullets.push(tmp);//TODO 在函數時會析構掉tmp，不知道是否會影響到queue裏的元素，待逐步調試時查證
}