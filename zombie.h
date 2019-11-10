#pragma once
#include "basic.h"
#include "creature.h"

//行走攻擊分開執行，每時隙只能執行其中一個
class ZOMBIE:private Creature //先實現普通僵尸
{
	bool attack_flag;
	void attack();
public:
	ZOMBIE();
	~ZOMBIE();

	void move(coordinate& position);

	void next(int clock,coordinate& position);
};

/*
TODO
不同種類的僵尸
*/