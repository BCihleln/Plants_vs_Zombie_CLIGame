#pragma once
#include "basic.h"
#include "creature.h"

class PLANT:private Creature
{
	//string name;
	int cost; // ����ꖹ┵
	//int HP;
	//int SPD;//speed ʹ�������g��
	//int ATK;
public:
	PLANT();
	PLANT(string name);
	//~PLANT();
};