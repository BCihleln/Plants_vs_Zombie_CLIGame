#include "plants.h"

PLANT::PLANT():Creature("None")
{
	cost = 0;
}

PLANT::~PLANT()
{
#ifdef DEBUG
	static int count = 0;
	cout << "destruct plant " << count<< endl;
	count++;
#endif
}

void PLANT::attack()
{
	//射擊型植物的攻擊方式是生產一顆子彈
	BULLET tmp(name,this->ATK,0);
	bullets.push(tmp);//TODO 在函數時會析構掉tmp，不知道是否會影響到queue裏的元素，待逐步調試時查證
}