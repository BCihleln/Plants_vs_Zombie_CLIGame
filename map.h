#pragma once

#include "basic.h"
#include "table.cpp"
	//需要找到基類函數的定義，故包含cpp
#include "plants.h"
#include "bullet.h"
#include "zombie.h"

//
//struct mapCell
//{
//	Plant plant;
//	BULLET* bullet;//當前單元格是否有子彈
//};

class Map
{
	Table<Plant> yard;//種植物的院子

	struct zombie_on_screen
	{
		Zombie zombie;//用zombie基類的引用管理派生類
		coordinate screen;//屏幕坐標
	};
	vector<zombie_on_screen> zombies[map_row];

	struct bullet_on_screen
	{
		BULLET bullet;
		coordinate screen;
	};
	queue<bullet_on_screen> bullets[map_row];


	int SunFlower_amount;

	//x : row_index, y : column_index
	bool has_plant(int x, int y);

	//TODO 處理植物、僵尸雙方攻擊
	void compute_attack();
	//TODO 維護僵尸、子彈移動坐標
	void comput_move();
	
	void generate_zombie();

	void init();
public:	
	friend class Display;
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


	//暫時給display類用，後面要刪除，因爲display類直接引入table的指針
	coordinate Screen2Cell_middle(coordinate screen_position)const
	{
		return yard.Screen2Cell_middle(screen_position);
	}

	string PlantOnXY(const Plant* target,coordinate position);

	int next(clock_t game_clock);
};