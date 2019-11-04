#pragma once
#include "basic.h"


class STORE
{
	struct product
	{
		int plant_ID;
		int cool_time;
	}products[store_row][store_column];//總共十二個可供購買的植物

	int sun;//當前玩家的陽光數

	//coordinate Screen2Store(coordinate target);
	coordinate Screen2Store(short x,short y);

public:
	STORE();

	void init();
	int select(coordinate position);
};