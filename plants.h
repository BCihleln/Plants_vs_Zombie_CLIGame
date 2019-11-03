#pragma once
#include "basic.h"
#include <queue>
#include "creature.h"
#include "bullet.h"

class PLANT:public Creature
{
	int cost; // 消耗陽光數
	queue<BULLET> bullets;//由植物生產的子彈隊列
public:
	PLANT();
	~PLANT();

	void attack();
};