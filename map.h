#pragma once

#include "basic.h"
#include "plants.h"
#include "zombie.h"

const int width = 5;
const int length = 7;

class MAP
{
	struct mapCell
	{
		PLANT* plant;
		ZOMBIE** zombie;//也許會有很多個zombie，可能要用vector結構存儲一個單元格裏面的所有zombie
		bool bullet;//當前單元格是否有子彈
	} map[width][length];

public:
	friend class GAME_SYSTEM;
	MAP();

	
	mapCell* operator[](int target)
	{
		if (target > length)
		{
			cout << "Reading map out of Range!\n";
			exit(0);
		}
		return map[target];
	}//重載[]來直接取得單元格數據
};