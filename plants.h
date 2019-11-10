#pragma once
#include "basic.h"
#include <queue>
#include "creature.h"
#include "bullet.h"

class Plant:private Creature //先只實現射擊型植物
{
	plant_ID ID_;
	int cost_; // 消耗陽光數
	int cool_time_;// 能再次購買的冷卻時間 單位：秒
	queue<BULLET> bullets;//由植物生產的子彈隊列
	void attack();
public:

	Plant();
	~Plant();

	void set_type(const plant_ID ID);
	void clean();
	int cost()const;
	int cool_time()const;
	plant_ID ID()const;
	string name()const;


	virtual void next(int clock);
};

/*TODO：
實現方式：繼承？
	BUFF型植物（eg 向日葵、大蒜
	一次性植物（eg 櫻桃、倭瓜）
	持續傷害（eg 地刺
*/