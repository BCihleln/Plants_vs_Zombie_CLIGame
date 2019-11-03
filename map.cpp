#include "map.h"

MAP::MAP()
{
	init();
}

MAP::~MAP()
{
	init();
}

void MAP::init()
{
	for (int i = 0; i < map_width; ++i)
		for (int j = 0; j < map_length; ++j)
			map[i][j] = { &plants[i][j],NULL,false };//把創建的空植物都種到地裏
}

void MAP::PlantOnXY(PLANT& target, int x, int y)
{
	map[y][x].plant = &target;
}
