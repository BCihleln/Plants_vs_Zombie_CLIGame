#include "plants.h"

Plant::Plant():Creature("None"),ID_(plant_ID::None)
{
	cost_ = 0;
	cool_time_ = 25;
}

Plant::~Plant()
{
//#ifdef DEBUG
//	static int count = 0;
//	cout << "destruct plant " << count<< endl;
//	count++;
//#endif
	//cout << this << endl;
}

//void Plant::set_type(const plant_ID& ID)
//{
//	if(this->ID_ ==plant_ID::None)//只能被設置一次
//	{
//		this->ID_ = ID;
//		switch (ID)
//		{
//		case	plant_ID::Sun_Flower:
//			this->name_ = "Sun Flower";
//			this->HP_ = 50;
//			this->ATK_ = 0;
//			this->ATK_SPD_ = 10;
//			this->cost_ = 25;
//			this->cool_time_ = 30;
//			return;
//		case plant_ID::Bean_Shooter://豌豆射手
//			this->name_ = "Bean Shooter";
//			this->HP_ = 60;
//			this->ATK_ = 25;
//			this->ATK_SPD_ = 50;
//			this->cost_ = 50;
//			this->cool_time_ = 15;
//			return;
//		case plant_ID::Nut_Wall://堅果墻
//			this->name_ = "Nut Wall";
//			this->HP_ = 500;
//			this->cost_ = 50;
//			this->cool_time_ = 25;
//			return;
//		default:
//			this->ID_ = plant_ID::None;
//			return;
//		}
//	}
//}

void Plant::clean() {	this->ID_ = plant_ID::None;	}

int Plant::cost() const {	return this->cost_;	}

int Plant::cool_time() const { 	return this->cool_time_;	}

plant_ID Plant::ID() const {	return this->ID_;	}

string Plant::name() const {	return this->name_;	}


//void Plant::attack()
//{
//	////射擊型植物的攻擊方式是生產一顆子彈
//	Bullet tmp(name_,this->ATK_,0);
//	bullets.push(tmp);//TODO 在函數時會析構掉tmp，不知道是否會影響到queue裏的元素，待逐步調試時查證
//	//TODO 生產子彈
//}

void Plant::die()
{
	name_ = "None";
	this->ID_ = plant_ID::None;
	HP_ = 0;
	ATK_ = 0;
	ATK_SPD_ = 0;
	cost_ = 0;
	cool_time_ = 0;
}

void Plant::next(int clock)
{
	if (HP_ > 0)//還活著的話
	{
		if (clock % ATK_SPD_ == 0)
			attack();
	}
}

Shooting_Plant::Shooting_Plant()
{
	attack_range_ = 10;
}

void Shooting_Plant::attack()
{

}

void Shooting_Plant::set_type(const plant_ID& ID)
{
	if(this->ID_ ==plant_ID::None)//只能被設置一次
	{
		this->ID_ = ID;
		switch (ID)
		{
		case plant_ID::Bean_Shooter://豌豆射手
			this->name_ = "Bean Shooter";
			this->HP_ = 60;
			this->ATK_ = 25;
			this->ATK_SPD_ = 50;
			this->cost_ = 30;
			this->cool_time_ = 15;
			return;
		case plant_ID::Double_Bean_Shooter:
			this->name_ = "Bean Shooter";
			this->HP_ = 80;
			this->ATK_ = 25;
			this->ATK_SPD_ = 50;
			this->cost_ = 50;
			this->cool_time_ = 20;
			return;
		case plant_ID::Triple_Bean_Shooter:
			this->name_ = "Bean Shooter";
			this->HP_ = 100;
			this->ATK_ = 25;
			this->ATK_SPD_ = 50;
			this->cost_ = 80;
			this->cool_time_ = 25;
			return;
		case plant_ID::Bean_Gatlin:
			this->name_ = "Bean Shooter";
			this->HP_ = 150;
			this->ATK_ = 25;
			this->ATK_SPD_ = 50;
			this->cost_ = 125;
			this->cool_time_ = 30;
			return;
		case plant_ID::Ice_Bean_Shooter:
			this->name_ = "Bean Shooter";
			this->HP_ = 60;
			this->ATK_ = 25;
			this->ATK_SPD_ = 50;
			this->cost_ = 50;
			this->cool_time_ = 15;
			return;
		default:
			this->ID_ = plant_ID::None;
			return;
		}
	}
}

void Shooting_Plant::next(int clock)
{
}



Explosive_Plant::Explosive_Plant()
{
}

void Explosive_Plant::attack()
{
}

void Explosive_Plant::set_type(const plant_ID& ID)
{
}

void Explosive_Plant::next(int clock)
{

}



Buff_Plant::Buff_Plant()
{

}

void Buff_Plant::attack()
{
}

void Buff_Plant::set_type(const plant_ID& ID)
{
}

void Buff_Plant::next(int clock)
{

}