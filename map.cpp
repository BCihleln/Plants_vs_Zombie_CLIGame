#include "map.h"

coordinate Map::Screen2Map(coordinate target)
{
	target.X /= cell_length;
	target.Y -= 10;
	target.Y /= cell_width;
	return target;
}

Map::Map()
{
	init();
}

Map::~Map()
{
	init();
}

void Map::init()
{
	for (int i = 0; i < map_row; ++i)
		for (int j = 0; j < map_column; ++j)
		{
			map[i][j] = { NULL,NULL };
		}
}

void Map::PlantOnXY(int target_ID, coordinate position)
{
	position = Screen2Map(position);
	plants[position.Y][position.X].set_type(target_ID);
}

Plant* Map::select(coordinate position)
{
	position = Screen2Map(position);
	return &plants[position.Y][position.X];
}
