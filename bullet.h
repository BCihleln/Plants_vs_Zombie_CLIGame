#pragma once
#include "creature.h"

class BULLET :private Creature//子彈作爲一種特殊的生物（突然想到的騷操作）
{	//TODO：繼承Zombie
	//子彈的坐標在地圖類中管理
	short effect;//子彈造成的效果代號
		/*
		0: 無特殊效果
		1: 減速（像是凍結、黏著等等）
		2: 穿甲（無視防禦）
		3: 即死
		4: 持續傷害（像是中毒、燒傷等等）
		5: 麻痹
		……
		*/
public:
	BULLET(string name, int attack,short effect);
	~BULLET();

	void next(int clock, coordinate& position);
};