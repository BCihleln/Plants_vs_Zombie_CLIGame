#pragma once

#include "basic.h"
#include "table.cpp"
//	//需要找到模板化基類成員函數的定義，故包含cpp
#include "plants.h"
#include "bullet.h"
#include "zombie.h"

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
		Bullet bullet;
		coordinate screen;
	};
	vector<bullet_on_screen> bullets[map_row];

	clock_t clock;
	int SunFlower_amount;

	//yard position
	bool has_plant(const coordinate position);

	void generate_zombie();
	int manage_zombie();
	void plant_attack();
	void manage_bullet();

	void init();
public:	
	friend class Display;
	Map();
	~Map();

	//暫時給display類用，TODO 後面要刪除，因爲計劃直接讓display類使用table指針
	coordinate Screen2Cell_middle(coordinate screen_position)const
	{
		return yard.Screen2Cell_middle(screen_position);
	}

	string PlantOnXY(const Plant* target,coordinate position);

	int next(clock_t game_clock);
};