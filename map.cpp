#include "map.h"

//coordinate Map::Screen2Map(coordinate target)
//{//TODO µØˆDß…½ç™z²é
//	target.X /= map_cell_length;
//	target.Y -= 10;
//	target.Y /= map_cell_width;
//	return target;
//}

Map::Map() :Table(map_row, map_column, { 0,10 }, { map_cell_length,map_cell_width })
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
	{
		for (int j = 0; j < map_column; ++j)
		{
			table[i][j] = { NULL,NULL };
		}
	}
}

void Map::PlantOnXY(const plant_list target_ID, coordinate position)
{
	position = Screen2Table(position);
	plants[position.Y][position.X].set_type(target_ID);
}

//Plant* Map::select(coordinate position)
//{
//	position = Screen2Map(position);
//	return &plants[position.Y][position.X];
//}
