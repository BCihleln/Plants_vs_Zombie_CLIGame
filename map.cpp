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


string Map::PlantOnXY(const plant_ID target_ID, coordinate position)
{
	mapCell* target = select(position,true);
	if (target != NULL)//³É¹¦ßx“ñ
	{
		if (target->plant.name == "plant_ID::None")
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

void Map::next()
{
}

//Plant* Map::select(coordinate position)
//{
//	position = Screen2Map(position);
//	return &plants[position.Y][position.X];
//}
