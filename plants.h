#pragma once
#include "basic.h"
#include <queue>
#include "creature.h"
#include "bullet.h"

class PLANT:public Creature
{
	int cost; // ����ꖹ┵
	queue<BULLET> bullets;//��ֲ�����a���ӏ����
public:
	PLANT();
	~PLANT();

	void attack();
};