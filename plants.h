#pragma once
#include "basic.h"
#include <queue>
#include "creature.h"
#include "bullet.h"

class Plant:private Creature //先只實現射擊型植物
{
	int cost; // 消耗陽光數
	int cool_time;// 能再次購買的冷卻時間 單位：秒
	queue<BULLET> bullets;//由植物生產的子彈隊列
public:
	plant_list ID;

	Plant();
	~Plant();

	void set_type(const plant_list ID);
	int get_cost()const;
	int get_cool_time()const;

	void attack();
};

/*TODO：
實現方式：繼承？
	BUFF型植物（eg 向日葵、大蒜
	一次性植物（eg 櫻桃、倭瓜）
	持續傷害（eg 地刺
*/