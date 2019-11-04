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
			products[i][j] = { NULL,0 };
}

int STORE::select(coordinate position)
{
	position = Screen2Store(position.X,position.Y);
	//cout << position;
	return products[position.Y][position.X].plant_ID;
}

