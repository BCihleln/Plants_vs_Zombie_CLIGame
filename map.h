#pragma once

#include "basic.h"
#include "table.cpp"
	//需要找到基類函數的定義，故包含cpp
#include "plants.h"
#include "bullet.h"
#include "zombie.h"


struct mapCell
{
	Plant plant;
	BULLET* bullet;//當前單元格是否有子彈
};

class Map:public Table <mapCell>
{
	struct zombie_on_screen
	{
		ZOMBIE zombie;
		coordinate screen;
	};
	vector<zombie_on_screen> zombies[map_row];

	int SunFlower_amount;

	//coordinate Screen2Map(coordinate target);
	//TODO 處理植物、僵尸雙方攻擊
	void compute_attack();
	//TODO 維護僵尸、子彈移動坐標
	void comput_move();
	
	//僵尸的管理 循環隊列，死掉的僵尸改名換姓后重新加入隊尾
	void generate_zombie();

	void init();
public:	
	Map();
	~Map();

	//mapCell* operator[](int target)
	//{
	//	if (target > map_column)
	//	{
	//		cout << "Reading map out of Range!\n";
	//		exit(0);
	//	}
	//	return map[target];
	//}//重載[]來直接取得單元格數據

	string PlantOnXY(const Plant* target,coordinate position);

	int next(clock_t game_clock);
};