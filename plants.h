#pragma once
#include "basic.h"
#include "creature.h"

class PLANT:private Creature
{
	//string name;
	int cost; // 消耗陽光數
	//int HP;
	//int SPD;//speed 使用能力間隔
	//int ATK;
public:
	PLANT();
	PLANT(string name);
	//~PLANT();
};