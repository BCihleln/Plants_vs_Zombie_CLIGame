#include "map.h"

Map::Map() :yard(map_row, map_column, { 0,10 }, { map_cell_length,map_cell_width }),
	SunFlower_amount(0)
{
	init();
}

Map::~Map()
{
}

//input yard position, make sure the position is indeed in the yard!!!
bool Map::has_plant(const coordinate position)
{
	//Plant a = yard[position];
	//plant_ID tmp =a.ID();
	//return tmp != plant_ID::None;
	return (yard[position].ID() != plant_ID::None);
}

void Map::generate_zombie()
{	//TODO:僵尸的管理 循環隊列，死掉的僵尸改名換姓后重新加入隊尾

	short y = rand() % map_row;

	Zombie tmp;
	tmp.change_type((tool_type)(rand()%10));
	//產生一隻隨機僵尸
	coordinate screen = {
		(map_cell_length+3) * map_column ,
		map_cell_width +y * map_cell_width + rand() % map_cell_width };

	zombies[y].push_back(zombie_on_screen{ tmp,screen });
}

void Map::init()
{
	//Plant tmp;
	//for (short i = 0; i < map_row; ++i)
	//{
	//	for (short j = 0; j < map_column; ++j)
	//	{
	//		yard[coordinate{ i,j }] = tmp;
	//	}
	//}
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

int Map::manage_zombie()
{
	if (clock % 100 == 0)//clock % rand() ==0 隨機時間產生僵尸
		generate_zombie();

	for (short i = 0; i < map_row; ++i)
	{
		for (short j = 0; j < (short)zombies[i].size(); ++j)// 全體僵尸行動！
		{
			Zombie& zombie = zombies[i][j].zombie;
			coordinate zombie_in_yard = yard.Screen2Table(zombies[i][j].screen, true);//僵尸在院子的坐標：返回院子内坐標 或 超界
			//bool tmp = zombie_in_yard != coordinate_out_of_border;
			//bool tmp2 = false;
			//if(tmp)
			//	tmp2 = has_plant(zombie_in_yard);
			bool obstacle =
				zombie_in_yard != coordinate_out_of_border
				&& has_plant(zombie_in_yard);//前方有植物
			//bool obstacle = tmp && tmp2;

			int damage = zombie.next(clock, zombies[i][j].screen, obstacle);
			if (obstacle)
			{
				Plant& attack_target = yard[zombie_in_yard];
				attack_target.injure(damage);
			}

			if (zombies[i][j].screen.X <= 0)//僵尸抵達最左邊
				return MAXINT;//游戲結束
		}
	}
	return 0;
}

void Map::plant_attack()
{
	//TODO 用vector把所有存在植物的指針儲存起來，管理時訪問這個隊列即可，不需要便利整個院子（提升微不足道的效率
	for (short i = 0; i < map_row; ++i)
	{
		for (short j = 0; j < map_column; ++j)//植物組織反擊！
			if (has_plant(coordinate{ i, j }))
			{
				Plant& target = yard[coordinate{ i,j }];
				target.next(clock);
			}
	}
}

void Map::manage_bullet()
{
	for(short i = 0;i<map_row;++i)
		for (short j = 0; j < bullets[i].size();++j)
		{
			Bullet& target = bullets[i][j].bullet;
			coordinate& position = bullets[i][j].screen;

			//position+=target.
		}
}

//若傳回值超過sun flower最大數量，則代表游戲結束，僵尸抵達最左邊
int Map::next(clock_t game_clock)
{
	clock = game_clock;

	int code = manage_zombie();
	if (code == MAXINT)//僵尸抵達最左邊，游戲結束
		return MAXINT;
	
	plant_attack();
	

//返回太陽花數量，用以給store增加sun數
	return SunFlower_amount;
}
