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
	int left_time;//ʣ�໺��ʱ�䣬��λ����
};

//TODO �^�б��
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
	string get_name_by_ID(plant_ID target);

	
	void buy();

	void next();
};