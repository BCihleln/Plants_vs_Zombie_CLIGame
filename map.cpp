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
{	//TODO:��ʬ�Ĺ��� ѭ�h��У������Ľ�ʬ�����Q�պ����¼����β

	short y = rand() % map_row;

	Zombie tmp;
	tmp.change_type((tool_type)(rand()%10));
	//�S�C�a��һ�b��ʬ
	//TODO ����S�C
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
	if (the_chosen_one != nullptr)//�ɹ��x��
	{
		if (the_chosen_one->ID() == plant_ID::None)
		{
			*the_chosen_one = *target;//�}�u���؈D��

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

//�����ֵ���^sun flower��������t�����Α�Y������ʬ���_����߅
int Map::next(clock_t game_clock)
{
	if(game_clock%100 == 0)
		generate_zombie();

	for (short i = 0; i < map_row; ++i)
	{
		for (short j = 0; j < (short)zombies[i].size(); ++j)// ȫ�w��ʬ�Єӣ�
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
			//if (tmp1 //��ʬ��Ժ����
			//	&& tmp2 //ǰ����ֲ��
			//	)
			//		obstacle = true;
			bool obstacle = 
				yard.in_table(zombies[i][j].screen) //��ʬ��Ժ����
				&& has_plant(i - 1, j);//ǰ����ֲ��

			int damage = zombies[i][j].zombie.next(game_clock, zombies[i][j].screen, obstacle);
			if(obstacle)
				yard[coordinate{ i,j }].injure(damage);

			if (zombies[i][j].screen.X <= 0)//��ʬ���_����߅
				return MAXINT;//�Α�Y��
		}

		for (short j = 0; j < map_column; ++j)//ֲ��M��������
			if (has_plant(i, j))
			{
				Plant& target = yard[coordinate{ i,j }];
				target.next(game_clock);
			}
	}
	return SunFlower_amount;//����̫ꖻ����������Խostore����sun��
}
