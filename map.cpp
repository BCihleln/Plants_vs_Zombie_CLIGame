#include "map.h"

Map::Map() :Table(map_row, map_column, { 0,10 }, { map_cell_length,map_cell_width })
{
	init();
}

Map::~Map()
{
}

void Map::init()
{
	for (int i = 0; i < map_row; ++i)
	{
		for (int j = 0; j < map_column; ++j)
		{
			this->table[i][j] = {Plant(), NULL,NULL };
		}
	}
}


string Map::PlantOnXY(const plant_list target_ID, coordinate position)
{
	mapCell* target = select(position,true);
	if (target != NULL)//³É¹¦ßx“ñ
	{
		if (target->plant.name == "None")
		{
			target->plant.set_type(target_ID);
			return target->plant.name;
		}
		else
			return string("Place already plant");
	}
	else
		return string("Out of Border");
}

//Plant* Map::select(coordinate position)
//{
//	position = Screen2Map(position);
//	return &plants[position.Y][position.X];
//}
