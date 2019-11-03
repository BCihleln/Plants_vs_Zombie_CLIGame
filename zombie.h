#pragma once
#include "basic.h"
#include "creature.h"

class ZOMBIE:public Creature
{

public:
	ZOMBIE();
	~ZOMBIE();

	int attack();
};