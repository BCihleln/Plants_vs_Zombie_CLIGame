#pragma once
#include "basic.h"
//#include "table.h"
#include "table.cpp"
#include "plants.h"

#define store_row 3
#define store_column 3
#define store_cell_size {38,2}
#define store_start_point {5,3}

struct product
{
	Plant plant;
	int left_time;//剩余缓冲时间，單位：秒
};

//TODO 繼承表類
class Store:public Table<product>
{

//products[store_row][store_column];//總共十二個可供購買的植物

	int sun;//當前玩家的陽光數

	//coordinate Screen2Store(coordinate target);
	//coordinate Screen2Store(short x,short y);

	void init();
public:
	Store();

	//返回選擇到的植物名
	string SelectProducts(coordinate screen);

	//返回植物指針，用於拷貝這個對象到地圖中
	Plant* buy(coordinate target);

	void next();
};