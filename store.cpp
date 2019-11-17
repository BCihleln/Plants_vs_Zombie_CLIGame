#include "store.h"

//coordinate Store::Screen2Store(short x, short y)
//{
//	x /= store_column;
//	y /= store_row;
//	return coordinate({ x,y });
//}

Store::Store() :Table(store_row, store_column, store_start_point,store_cell_size),
	the_chosen_one(nullptr)
{
	init();
}

void Store::init()
{
	sun = 25;
	//sun = 10000;
	for (int i = 0; i < store_row; ++i)
		for (int j = 0; j < store_column; ++j)
		{
			table[i][j].left_time = 0;
		}

	table[0][0].plant.set_type(plant_ID::Sun_Flower);
	table[0][1].plant.set_type(plant_ID::Bean_Shooter);
	table[0][2].plant.set_type(plant_ID::Nut_Wall);
}

Plant* Store::SelectProducts(coordinate screen)
{
	the_chosen_one = select(screen, false);
	//cout << position;
	if (the_chosen_one == nullptr || //超界
		the_chosen_one->left_time >0 || //緩衝未到
		the_chosen_one->plant.cost() > sun //費用不足
		)
	{
		//return string("Out of border");
		//this->the_chosen_one = nullptr;//選擇失敗
		return nullptr;//(Plant*)the_chosen_one
	}
	else
	{
		return &the_chosen_one->plant;
	}
}

//string Store::get_name_by_ID(plant_ID target)
//{
//	Plant tmp;
//	tmp.set_type(target);
//	return tmp.name;
//}

void Store::buy()
{
	if (the_chosen_one == nullptr)
	{
		cout << __FUNCTION__ << "error!" << endl;
		exit(0);
	}

	sun -= the_chosen_one->plant.cost();
	the_chosen_one->left_time = the_chosen_one->plant.cool_time();//設置緩衝時間
}

void Store::next(clock_t game_clock, int sun_flower_amount)
{

 //	clock_t duration = game_clock - last_game_clock;
	//while(duration>1000)//同步於1秒
	//{
	//	for (int i = 0; i < store_row; ++i)
	//		for (int j = 0; j < store_column; ++j)
	//			if (table[i][j].left_time > 0)
	//				table[i][j].left_time--;
	//	sun += sun_flower_amount*10 + 5; 

	//	duration -= 1000;
	//}
	if(game_clock % 10==0)//同步於1秒
	{
		for (int i = 0; i < store_row; ++i)
			for (int j = 0; j < store_column; ++j)
				if (table[i][j].left_time > 0)
					table[i][j].left_time--;
		sun += sun_flower_amount;
		if (game_clock % 50 == 0)//每五秒產生2個陽光
			sun += 2;
	}
}

