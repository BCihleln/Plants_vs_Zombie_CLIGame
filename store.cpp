#include "store.h"

//coordinate Store::Screen2Store(short x, short y)
//{
//	x /= store_column;
//	y /= store_row;
//	return coordinate({ x,y });
//}

Store::Store() :Table(store_row, store_column, store_start_point,store_cell_size)
{
	init();
}

void Store::init()
{
	//sun = 0;
	sun = 10000;
	for (int i = 0; i < store_row; ++i)
		for (int j = 0; j < store_column; ++j)
		{
			table[i][j].left_time = 0;
		}

	table[0][0].plant.set_type(plant_ID::Sun_Flower);
	table[1][0].plant.set_type(plant_ID::Bean_Shooter);
	table[2][0].plant.set_type(plant_ID::Nut_Wall);
}

Plant* Store::SelectProducts(coordinate screen)
{
	product* target = this->select(screen, false);
	//cout << position;
	if (target == nullptr || //超界
		target->left_time >0 || //緩衝未到
		target->plant.get_cost() > sun //費用不足
		)
	{
		//return string("Out of border");
		this->the_chosen_one = nullptr;
		//return plant_ID::None;//不能選擇
		return nullptr;
	}
	else
	{
		this->the_chosen_one = target;
		return &the_chosen_one->plant;
	}
}

string Store::get_name_by_ID(plant_ID target)
{
	Plant tmp;
	tmp.set_type(target);
	return tmp.name;
}

void Store::buy()
{
	sun -= the_chosen_one->plant.get_cost();
	the_chosen_one->left_time = the_chosen_one->plant.get_cool_time();//設置緩衝時間
	//return &table[target.Y][target.X].plant;
}

void Store::next()
{
	for (int i = 0; i < store_row; ++i)
		for (int j = 0; j < store_column; ++j)
			if (table[i][j].left_time > 0)
				table[i][j].left_time--;

	sun++;
	//TODO sun += amount_of_sun_flower * 10 考慮用變量存 每時隙增加的陽光數
}

