#pragma once
#include "basic.h"

class Creature
{
protected:
	int
		HP,
		ATK, ATK_SPD,//ATK Speed ����
		SPD,//�Ƅ��ٶ�
		DEF;//�ٷֱȷ��R�����99%
public:
	string name;

	//Creature();
	Creature(string name);
	//~Creature();

	string get_name();

	void injure(int damage);
	void die();
};