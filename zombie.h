#pragma once
#include "basic.h"
#include "creature.h"

//���߹������_���У�ÿ�r϶ֻ�܈�������һ��
class ZOMBIE:private Creature //�Ȍ��F��ͨ��ʬ
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
��ͬ�NĽ�ʬ
*/