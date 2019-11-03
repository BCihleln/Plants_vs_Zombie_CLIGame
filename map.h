#pragma once

#include "basic.h"
#include "plants.h"
#include "zombie.h"

class MAP
{
	struct mapCell
	{
		PLANT* plant;
		ZOMBIE** zombie;//也許會有很多個zombie，可能要用vector結構存儲一個單元格裏面的所有zombie
		bool bullet;//當前單元格是否有子彈
	} map[map_width][map_length];

	PLANT plants[map_width][map_length];
	vector<ZOMBIE> zombies[map_width];

public:
	friend class GAME_SYSTEM;
	MAP();
	~MAP();

	void init();

	
	mapCell* operator[](int target)
	{
		if (target > map_length)
		{
			cout << "Reading map out of Range!\n";
			exit(0);
		}
		return map[target];
	}//重載[]來直接取得單元格數據

	void PlantOnXY(PLANT& target, int x, int y);

	//TODO 需要維護子彈、僵尸的坐標（持續移動）

	//僵尸的管理 循環隊列，死掉的僵尸改名換姓后重新加入隊尾
};