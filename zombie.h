#pragma once
#include "basic.h"
#include "creature.h"

class ZOMBIE:private Creature //�Ȍ��F��ͨ��ʬ
{

public:
	ZOMBIE();
	~ZOMBIE();

	int attack();
};

/*
TODO
��ͬ�NĽ�ʬ
*/