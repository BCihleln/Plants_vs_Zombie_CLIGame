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
	int left_time;//ʣ�໺��ʱ�䣬��λ����
};

class Store:public Table<product>
{

//products[store_row][store_column];//����ʮ�����ɹ�ُ�I��ֲ��

	int sun;//��ǰ��ҵ�ꖹ┵

	//coordinate Screen2Store(coordinate target);
	//coordinate Screen2Store(short x,short y);

	void init();
public:
	Store();

	//�����x�񵽵�ֲ��ָ�
	Plant* SelectProducts(coordinate screen);
	//string get_name_by_ID(plant_ID target);

	
	void buy();

	void next(clock_t game_clock,int sun_flower_amount);
};