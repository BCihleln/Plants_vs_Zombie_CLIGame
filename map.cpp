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
			this->table[i][j] = {Plant(), nullptr };
		}
	}
	SunFlower_amount = 0;
}


string Map::PlantOnXY(const Plant* target, coordinate position)
{
	select(position,true);
	if (the_chosen_one != nullptr)//成功選擇
	{
		if (the_chosen_one->plant.ID() == plant_ID::None)
		{
			the_chosen_one->plant = *target;//複製到地圖中
			
			if (the_chosen_one->plant.ID() == plant_ID::Sun_Flower)
				SunFlower_amount++;

			return the_chosen_one->plant.name();
		}
		else
		{
			the_chosen_one = nullptr;
			return string("Place already plant");
		}
	}
	else
		return string("Out of Border");
}

int Map::next(clock_t game_clock)
{
	for(int i = 0;i<map_row;++i)
	{
		for (int j = 0; j < zombies[i].size(); ++j)// 全體僵尸行動！
			zombies[i][j].zombie.next(game_clock,zombies[i][j].screen);

		for(int j = 0;j<map_column;++j)//植物組織反擊！
			if (table[i][j].plant.ID() != plant_ID::None)
			{
				table[i][j].plant.next(game_clock);

			}
	}
	return SunFlower_amount;//返回太陽花數量，用以給store增加sun數
}
