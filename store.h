#pragma once
#include "basic.h"


class STORE
{
	struct product
	{
		int plant_ID;
		int cool_time;
	}products[store_row][store_column];//����ʮ�����ɹ�ُ�I��ֲ��

	int sun;//��ǰ��ҵ�ꖹ┵

	//coordinate Screen2Store(coordinate target);
	coordinate Screen2Store(short x,short y);

public:
	STORE();

	void init();
	int select(coordinate position);
};