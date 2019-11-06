#pragma once
#include "basic.h"
#include "plants.h"

//TODO 繼承表類
class STORE
{
	struct product
	{
		Plant plant;
		int left_time;//剩余缓冲时间，單位：秒
	}products[store_row][store_column];//總共十二個可供購買的植物

	int sun;//當前玩家的陽光數

	//coordinate Screen2Store(coordinate target);
	coordinate Screen2Store(short x,short y);

	void init();
public:
	STORE();

	coordinate select(coordinate position);

	Plant* buy(coordinate target);

	void next();
};