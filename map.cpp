#include "map.h"

//coordinate Map::Screen2Map(coordinate target)
//{//TODO µØˆDß…½ç™z²é
//	target.X /= map_cell_length;
//	target.Y -= 10;
//	target.Y /= map_cell_width;
//	return target;
//}

//template <class T>
Map::Map() :Table(map_row, map_column, { 0,10 }, { map_cell_length,map_cell_width })
{
	init();
}

//template <class T>
Map::~Map()
{
}
//template <class T>
void Map::init()
{
	for (int i = 0; i < map_row; ++i)
	{
		for (int j = 0; j < map_column; ++j)
		{
			this->table[i][j] = { NULL,NULL };
		}
	}
}

//template <class T>
void Map::PlantOnXY(const plant_list target_ID, coordinate position)
{
	position = this->Table::Screen2Table(position);
	plants[position.Y][position.X].set_type(target_ID);
}

//Plant* Map::select(coordinate position)
//{
//	position = Screen2Map(position);
//	return &plants[position.Y][position.X];
//}
