#pragma once
#include "basic.h"
#include "table.cpp"
//	//��Ҫ�ҵ�ģ�廯��ɆT�����Ķ��x���ʰ���cpp
#include "plants.h"

#define store_row 1
#define store_column 6
#define store_cell_size {18,6}
#define store_start_point {18,3}

struct product
{
	Plant plant;
	int left_time;//ʣ�໺��ʱ�䣬��λ����
};

class Store:public Table<product>
{

	/*
	TODO: ��mapһ�ӸĠ� �ۺ�table
	*/
	int sun;//��ǰ��ҵ�ꖹ┵
	
	product* the_chosen_one;
	void init();
public:
	friend class Display;
	Store();

	//�����x�񵽵�ֲ��ָ�
	Plant* SelectProducts(coordinate screen);
	//string get_name_by_ID(plant_ID target);

	
	void buy();

	void next(clock_t game_clock,int sun_flower_amount);
};