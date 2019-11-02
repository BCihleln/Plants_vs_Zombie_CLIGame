#include "creature.h"

Creature::Creature()
{

}


Creature::Creature(string name):
	name(name),
	HP(50),//��헔�ֵ0~100
	ATK(2),
	ATK_SPD(1),//ATK_SPD���HӋ�㣺1500ms /ATK_SPD
	SPD(0),
	DEF(0)
{
}

void Creature::injure(int damage)
{
	HP -= (damage * DEF / 100);
}
