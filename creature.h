#pragma once
#include "basic.h"

class Creature
{
	
public:
	string name;
	int
		HP,
		ATK,ATK_SPD,//ATK Speed ����
		SPD,//�Ƅ��ٶ�
		DEF;

	Creature();
	Creature(string name);
	//~Creature();

	void injure(int damage);
	void die();
};