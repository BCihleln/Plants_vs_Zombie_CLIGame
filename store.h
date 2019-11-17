#pragma once
#include "basic.h"
#include "table.cpp"
//	//需要找到模板化基類成員函數的定義，故包含cpp
#include "plants.h"

#define store_row 1
#define store_column 6
#define store_cell_size {18,6}
#define store_start_point {18,3}

struct product
{
	Plant plant;
	int left_time;//剩余缓冲时间，單位：秒
};

class Store:public Table<product>
{

	/*
	TODO: 像map一樣改爲 聚合table
	*/
	int sun;//當前玩家的陽光數
	
	product* the_chosen_one;
	void init();
public:
	friend class Display;
	Store();

	//返回選擇到的植物指針
	Plant* SelectProducts(coordinate screen);
	//string get_name_by_ID(plant_ID target);

	
	void buy();

	void next(clock_t game_clock,int sun_flower_amount);
};