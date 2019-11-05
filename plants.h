#pragma once
#include "basic.h"
#include <queue>
#include "creature.h"
#include "bullet.h"

class Plant:protected Creature //先只實現射擊型植物
{
	plant_list ID;
protected:
	int cost; // 消耗陽光數
	queue<BULLET> bullets;//由植物生產的子彈隊列
public:
	Plant();
	~Plant();

	void set_type(const plant_list ID);

	void attack();
};

/*TODO：
實現方式：繼承？
	BUFF型植物（eg 向日葵、大蒜
	一次性植物（eg 櫻桃、倭瓜）
	持續傷害（eg 地刺
*/