#include "creature.h"

Creature::Creature()
{

}


Creature::Creature(string name):
	name(name),
	HP(50),//¸÷í—”µÖµ0~100
	ATK(2),
	ATK_SPD(1),//ATK_SPDŒëHÓ‹Ëã£º1500ms /ATK_SPD
	SPD(0),
	DEF(0)
{
}

void Creature::injure(int damage)
{
	HP -= (damage * DEF / 100);
}
