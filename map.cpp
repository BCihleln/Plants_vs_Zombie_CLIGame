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


coordinate Map::PlantOnXY(const plant_list target_ID, coordinate position)
{
	if (this->Table::Screen2Table(position, true) != coordinate_out_of_border)
	{
		position = this->Table::Screen2Table(position, true);
		table[position.Y][position.X].plant.set_type(target_ID);
		return position;
	}
	else
		return coordinate_out_of_border;
}

//Plant* Map::select(coordinate position)
//{
//	position = Screen2Map(position);
//	return &plants[position.Y][position.X];
//}
