#pragma once

#include "basic.h"
#include "table.cpp"
	//��Ҫ�ҵ�������Ķ��x���ʰ���cpp
#include "plants.h"
#include "bullet.h"
#include "zombie.h"


struct mapCell
{
	Plant plant;
	BULLET* bullet;//��ǰ��Ԫ���Ƿ����ӏ�
};

class Map:public Table <mapCell>
{
	struct zombie_on_screen
	{
		ZOMBIE zombie;
		coordinate screen;
	};
	vector<zombie_on_screen> zombies[map_row];

	int SunFlower_amount;

	//coordinate Screen2Map(coordinate target);
	//TODO ̎��ֲ���ʬ�p������
	void compute_attack();
	//TODO �S�o��ʬ���ӏ��Ƅ�����
	void comput_move();
	
	//��ʬ�Ĺ��� ѭ�h��У������Ľ�ʬ�����Q�պ����¼����β
	void generate_zombie();

	void init();
public:	
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

	string PlantOnXY(const Plant* target,coordinate position);

	int next(clock_t game_clock);
};