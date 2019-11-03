#include "creature.h"

Creature::Creature(string name):
	name(name),
	HP(50),//¸÷í—”µÖµ0~100
	ATK(20),
	ATK_SPD(1),//ATK_SPDŒëHÓ‹Ëã£º1500ms /ATK_SPD
	SPD(0),
	DEF(0)
{
}

void Creature::injure(int damage)
{
	HP -= (damage * (DEF-1) / 100);
	if (HP < 1)
		die();
}

void Creature::die()
{
	name = "died " + name;
	HP = 0;
	ATK = 0;
	ATK_SPD = 0;
	SPD = 0;
	DEF = 0;
}
