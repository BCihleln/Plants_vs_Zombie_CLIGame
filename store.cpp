#include "store.h"

coordinate STORE::Screen2Store(short x, short y)
{
	x /= store_column;
	y /= store_row;
	return coordinate({ x,y });
}

STORE::STORE()
{
	init();
}

void STORE::init()
{
	sun = 0;
	for (int i = 0; i < 2; ++i)
		for (int j = 0; j < 6; ++j)
		{
			products[i][j].left_time = 0;
		}

	products[0][0].plant.set_type(Sun_Flower);
	products[0][1].plant.set_type(Bean_Shooter);
	products[0][2].plant.set_type(Nut_Wall);
}

coordinate STORE::select(coordinate position)
{
	position = Screen2Store(position.X,position.Y);
	//cout << position;
	if (products[position.Y][position.X].plant.get_cost() < sun)
		return position;
	else
		return { store_row,store_column };//費用不足，不能選擇
}

Plant* STORE::buy(coordinate target)
{
	sun -= products[target.Y][target.X].plant.get_cost();
	return &products[target.Y][target.X].plant;
}

void STORE::next()
{
	for (int i = 0; i < store_row; ++i)
		for (int j = 0; j < store_column; ++j)
			if (products[i][j].left_time > 0)
				products[i][j].left_time--;

	sun++;
	//TODO sun += amount_of_sun_flower * 10 考慮用變量存 每時隙增加的陽光數
}

