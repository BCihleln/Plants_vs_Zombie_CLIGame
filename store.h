#pragma once
#include "basic.h"
#include "plants.h"

//TODO �^�б��
class STORE
{
	struct product
	{
		Plant plant;
		int left_time;//ʣ�໺��ʱ�䣬��λ����
	}products[store_row][store_column];//����ʮ�����ɹ�ُ�I��ֲ��

	int sun;//��ǰ��ҵ�ꖹ┵

	//coordinate Screen2Store(coordinate target);
	coordinate Screen2Store(short x,short y);

	void init();
public:
	STORE();

	coordinate select(coordinate position);

	Plant* buy(coordinate target);

	void next();
};