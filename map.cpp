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
{	//TODO:��ʬ�Ĺ��� ѭ�h��У������Ľ�ʬ�����Q�պ����¼����β

	short y = rand() % map_row;

	Zombie tmp;
	tmp.change_type((tool_type)(rand()%10));
	//�a��һ�b�S�C��ʬ
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

int Map::manage_zombie()
{
	if (clock % 100 == 0)//clock % rand() ==0 �S�C�r�g�a����ʬ
		generate_zombie();

	for (short i = 0; i < map_row; ++i)
	{
		for (short j = 0; j < (short)zombies[i].size(); ++j)// ȫ�w��ʬ�Єӣ�
		{
			Zombie& zombie = zombies[i][j].zombie;
			coordinate zombie_in_yard = yard.Screen2Table(zombies[i][j].screen, true);//��ʬ��Ժ�ӵ����ˣ�����Ժ�������� �� ����
			//bool tmp = zombie_in_yard != coordinate_out_of_border;
			//bool tmp2 = false;
			//if(tmp)
			//	tmp2 = has_plant(zombie_in_yard);
			bool obstacle =
				zombie_in_yard != coordinate_out_of_border
				&& has_plant(zombie_in_yard);//ǰ����ֲ��
			//bool obstacle = tmp && tmp2;

			int damage = zombie.next(clock, zombies[i][j].screen, obstacle);
			if (obstacle)
			{
				Plant& attack_target = yard[zombie_in_yard];
				attack_target.injure(damage);
			}

			if (zombies[i][j].screen.X <= 0)//��ʬ���_����߅
				return MAXINT;//�Α�Y��
		}
	}
	return 0;
}

void Map::plant_attack()
{
	//TODO ��vector�����д���ֲ���ָᘃ�����������r�L���@����м��ɣ�����Ҫ��������Ժ�ӣ�����΢�������Ч��
	for (short i = 0; i < map_row; ++i)
	{
		for (short j = 0; j < map_column; ++j)//ֲ��M��������
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

//�����ֵ���^sun flower��������t�����Α�Y������ʬ���_����߅
int Map::next(clock_t game_clock)
{
	clock = game_clock;

	int code = manage_zombie();
	if (code == MAXINT)//��ʬ���_����߅���Α�Y��
		return MAXINT;
	
	plant_attack();
	

//����̫ꖻ����������Խostore����sun��
	return SunFlower_amount;
}
