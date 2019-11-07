#pragma once

#include "basic.h"
//#include "table.h"
#include "table.cpp"
#include "plants.h"
#include "bullet.h"
#include "zombie.h"


struct mapCell
{
	Plant plant;
	ZOMBIE* zombie;//Ҳ�S���кܶ���zombie������Ҫ��vector�Y���惦һ����Ԫ���Y�������zombie
	BULLET* bullet;//��ǰ��Ԫ���Ƿ����ӏ�
};

class Map:public Table <mapCell>
{
	vector<ZOMBIE> zombies[map_row];

	//coordinate Screen2Map(coordinate target);
	//TODO ̎��ֲ���ʬ�p������
	void compute_attack();
	//TODO �S�o��ʬ���ӏ��Ƅ�����
	void comput_move();
	
	//��ʬ�Ĺ��� ѭ�h��У������Ľ�ʬ�����Q�պ����¼����β
	void generate_zombie();

	void init();
public:
	friend class GAME_SYSTEM;
	
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

	//�Nֲ�ɹ���Ԓ����true����֮false
	string PlantOnXY(const plant_list target_ID,coordinate position);

};