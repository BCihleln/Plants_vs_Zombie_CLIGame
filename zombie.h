#pragma once
#include "basic.h"
#include "creature.h"

class ZOMBIE:private Creature //先實現普通僵尸
{

public:
	ZOMBIE();
	~ZOMBIE();

	int attack();
};

/*
TODO
不同種類的僵尸
*/