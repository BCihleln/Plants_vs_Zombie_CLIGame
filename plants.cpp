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
	//�����ֲ��Ĺ�����ʽ�����aһ�w�ӏ�
	BULLET tmp(name,this->ATK,0);
	bullets.push(tmp);//TODO �ں����r��������tmp����֪���Ƿ��Ӱ푵�queue�Y��Ԫ�أ������{ԇ�r���C
}