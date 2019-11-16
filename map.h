#pragma once

#include "basic.h"
#include "table.cpp"
//	//��Ҫ�ҵ�ģ�廯��ɆT�����Ķ��x���ʰ���cpp
#include "plants.h"
#include "bullet.h"
#include "zombie.h"

//
//struct mapCell
//{
//	Plant plant;
//	BULLET* bullet;//��ǰ��Ԫ���Ƿ����ӏ�
//};

class Map
{
	Table<Plant> yard;//�Nֲ���Ժ��

	struct zombie_on_screen
	{
		Zombie zombie;//��zombie������ù��������
		coordinate screen;//��Ļ����
	};
	vector<zombie_on_screen> zombies[map_row];

	struct bullet_on_screen
	{
		BULLET bullet;
		coordinate screen;
	};
	queue<bullet_on_screen> bullets[map_row];


	int SunFlower_amount;

	//x : row_index, y : column_index
	bool has_plant(int x, int y);

	//void compute_attack();

	//void comput_move();
	
	void generate_zombie();

	void init();
public:	
	friend class Display;
	Map();
	~Map();

	//mapCell* operator[](int target)
	//{
	//	if (target > map_column)
	//	{
	//		cout << "Reading map out of Range!\n";
	//		exit(0);
	//	}
	//	return map[target];
	//}//���d[]��ֱ��ȡ�Æ�Ԫ�񔵓�


	//���r�odisplay��ã�����Ҫ�h������display�ֱ������table��ָ�
	coordinate Screen2Cell_middle(coordinate screen_position)const
	{
		return yard.Screen2Cell_middle(screen_position);
	}

	string PlantOnXY(const Plant* target,coordinate position);

	int next(clock_t game_clock);
};