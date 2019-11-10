#pragma once
#include "basic.h"
#include "table.cpp"
#include "plants.h"

#define store_row 1
#define store_column 6
#define store_cell_size {18,5}
#define store_start_point {22,4}

struct product
{
	Plant plant;
	int left_time;//剩余缓冲时间，單位：秒
};

class Store:public Table<product>
{

//products[store_row][store_column];//總共十二個可供購買的植物

	int sun;//當前玩家的陽光數

	//coordinate Screen2Store(coordinate target);
	//coordinate Screen2Store(short x,short y);

	void init();
public:
	Store();

	//返回選擇到的植物指針
	Plant* SelectProducts(coordinate screen);
	//string get_name_by_ID(plant_ID target);

	
	void buy();

	void next(clock_t game_clock,int sun_flower_amount);
};