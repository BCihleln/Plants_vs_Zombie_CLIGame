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


string Map::PlantOnXY(const Plant* target, coordinate position)
{
	the_chosen_one = select(position,true);
	if (the_chosen_one != NULL)//成功選擇
	{
		if (the_chosen_one->plant.get_ID() == plant_ID::None)
		{
			the_chosen_one->plant = *target;//複製到地圖中
			//target->plant.set_type(target_ID);
			return the_chosen_one->plant.name;
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
