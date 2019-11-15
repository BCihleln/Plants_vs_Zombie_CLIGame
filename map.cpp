#include "map.h"

Map::Map() :yard(map_row, map_column, { 0,10 }, { map_cell_length,map_cell_width }),
	SunFlower_amount(0)
{
	init();
}

Map::~Map()
{
}

bool Map::has_plant(int x, int y)
{
	x = x < 0 ? 0 : x;
	y = y < 0 ? 0 : y;
	return (yard[coordinate{ (short)x,(short)y }].ID() != plant_ID::None);
}

void Map::generate_zombie()
{	//TODO:僵尸的管理 循環隊列，死掉的僵尸改名換姓后重新加入隊尾

	short y = rand() % map_row;

	Zombie tmp;
	tmp.change_type((tool_type)(rand()%10));
	//隨機產生一隻僵尸
	//TODO 類型隨機
	coordinate screen = {
		map_cell_length * map_column + rand() % 100 ,
		map_cell_width +y * map_cell_width + rand() % map_cell_width };

	zombies[y].push_back(zombie_on_screen{ tmp,screen });
}

void Map::init()
{
	Plant tmp;
	for (short i = 0; i < map_row; ++i)
	{
		for (short j = 0; j < map_column; ++j)
		{
			yard[coordinate{ i,j }] = tmp;
		}
	}
	SunFlower_amount = 0;
}


string Map::PlantOnXY(const Plant* target, coordinate position)
{
	Plant* the_chosen_one = yard.select(position, true);
	if (the_chosen_one != nullptr)//成功選擇
	{
		if (the_chosen_one->ID() == plant_ID::None)
		{
			*the_chosen_one = *target;//複製到地圖中

			if (the_chosen_one->ID() == plant_ID::Sun_Flower)
				SunFlower_amount++;

			return the_chosen_one->name();
		}
		else
		{
			//the_chosen_one = nullptr;
			return string("Place already plant");
		}
	}
	else
		return string("Out of Border");
}

//若傳回值超過sun flower最大數量，則代表游戲結束，僵尸抵達最左邊
int Map::next(clock_t game_clock)
{
	if(game_clock%100 == 0)
		generate_zombie();

	for (short i = 0; i < map_row; ++i)
	{
		for (short j = 0; j < (short)zombies[i].size(); ++j)// 全體僵尸行動！
		{
			//bool obstacle = false;
			//bool tmp1 = yard.in_table(zombies[i][j].screen);
			//bool tmp2 = false;
			//
			//
			//if (tmp1)
			//{
			//	coordinate a = yard.Screen2Table(zombies[i][j].screen, true);
			//	tmp2 = has_plant(a.Y,a.X);
			//}
			//if (tmp1 //僵尸在院子内
			//	&& tmp2 //前方有植物
			//	)
			//		obstacle = true;
			bool obstacle = 
				yard.in_table(zombies[i][j].screen) //僵尸在院子内
				&& has_plant(i - 1, j);//前方有植物

			int damage = zombies[i][j].zombie.next(game_clock, zombies[i][j].screen, obstacle);
			if(obstacle)
				yard[coordinate{ i,j }].injure(damage);

			if (zombies[i][j].screen.X <= 0)//僵尸抵達最左邊
				return MAXINT;//游戲結束
		}

		for (short j = 0; j < map_column; ++j)//植物組織反擊！
			if (has_plant(i, j))
			{
				Plant& target = yard[coordinate{ i,j }];
				target.next(game_clock);
			}
	}
	return SunFlower_amount;//返回太陽花數量，用以給store增加sun數
}
